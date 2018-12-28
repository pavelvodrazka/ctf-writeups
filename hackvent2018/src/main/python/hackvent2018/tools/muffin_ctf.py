import re

from pwn import *
import requests


FLAG_FORMAT = 'muffinCTF{[a-f0-9]{40}}'
AUTH_TOKEN = '${YOUR_AUTH_TOKEN_HERE}'


# API Calls
# ----------------------------------------------------

def do_api_request(endpoint, json_post_data):
    json_post_data['AUTH_TOKEN'] = AUTH_TOKEN

    with log.progress('Requesting API at endpoint /{0}'.format(endpoint)) as request_api_progress:
        return_json = requests.post(
            ('http://whale.hacking-lab.com:9180/' + endpoint),
            json = json_post_data
        ).json()

    return return_json


def submit_flags(flags):
    # submit flags to api
    return do_api_request('api/post_flags', {
        'flags' : flags
    })


def get_players():
    # get players from api
    return do_api_request('api/get_players', {})['players']


# ----------------------------------------------------


def extract_flags(input_text):
    # extract flags from input text
    return re.findall(FLAG_FORMAT, input_text)


def attack_player(service, player_name, exploit_func):
    # attacks a player service by using a defined exploit function

    attack_url = 'http://whale.hacking-lab.com:9182/{0}/{1}/'.format(player_name, service)

    return_input = exploit_func(attack_url)
    return extract_flags(return_input)


def attack_all(service, exploit_func):
    # attack all players for a particular service using a defined exploit function

    with log.progress('Attacking players') as attacking_players_progress:
        flags = []
        player_counter = 0
        players = get_players()
        for player in players:
            attacking_players_progress.status('Attacking players [{0}/{1}]'.format(str(player_counter+1), len(players)))

            with log.progress('Attacking player ' + player) as attacking_player_progress:
                curr_flags = attack_player(service, player, exploit_func)
                if len(curr_flags) == 0:
                    log.failure('Found no flags for player {0}'.format(player))
                else:
                    curr_flag_counter = 1
                    for curr_flag in curr_flags:
                        log.success('Found flag #{0} , player = {1}, flag = {2}'.format(len(flags)+curr_flag_counter, player, curr_flag))
                        curr_flag_counter += 1

                flags += curr_flags
            player_counter += 1


    with log.progress('Submitting flags') as submitting_flags_progress:
        flag_results = submit_flags(flags)['results']

        for flag_result in flag_results:
            submitted_flag_result = flag_result['result']
            submitted_flag = flag_result['flag']
            if submitted_flag_result == 'flag_not_found':
                log.failure('Flag {0} not found'.format(submitted_flag))
            if submitted_flag_result == 'flag_already_submitted':
                log.failure('Flag {0} already submitted'.format(submitted_flag))
            if submitted_flag_result == 'flag_too_old':
                log.failure('Flag {0} too old'.format(submitted_flag))
            if submitted_flag_result == 'flag_submitted':
                log.success('Flag {0} submitted'.format(submitted_flag))


print '''
           ___ ___ _     _____ _____ _____
 _____ _ _|  _|  _|_|___|     |_   _|   __|
|     | | |  _|  _| |   |   --| | | |   __|
|_|_|_|___|_| |_| |_|_|_|_____| |_| |__|   [Hackvent 2018]

    << Attack Library >>'''
