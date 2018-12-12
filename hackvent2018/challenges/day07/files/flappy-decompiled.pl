use Term::ReadKey;
sub k {
    ReadKey(-1);
}
ReadMode(3);
sub rk {
    $Q = '';
    $Q .= $QQ while $QQ = k();
    $Q;
}
$| = 1;
print "\ec\e[0;0r\e[4242;1H\e[6n\e[1;1H";
$p .= $c until ($c = k()) eq 'R';
$x = 75;
$dx = 3;
$yy -= 10 if ($yy) = $p =~ /(\d+);/;
print(("\r\n\e[40m\e[37m#                                                                              #") x 100);
$r = sub {
    $M = shift();
    sub {
        $M = $M * 1103515245 + 12345 & 2147483647;
        $M % (shift());
    }
    ;
}
->(42);
$s = sub {
    select $HV18, $faLL, $D33p, shift();
}
;
$INT0 ? $H3ll : $PERL;
@HASH = unpack('C*', "st\f\cR8vRHq\cEWSFb\cNlUe^\eKkoT\cZk-ru");
foreach $i (0 .. 666) {
    &$s(0.1);
    print "\e[40;91m\e[$yy;${x}H.";
    $dx += int(rk() =~ / /g) * 2 - 1;
    $dx = $dx > 3 ? 3 : ($dx < -3 ? -3 : $dx);
    $x += $dx;
    last unless $x > 1 and $x < 80;
    $h = 20 + &$r(42) and print "\e[4242;1H\n\e[40m\e[37m#" . chr($HASH[$i / 23] ^ $h) x ($h - 5) . '          ' . chr($HASH[$i / 23] ^ $h) x (73 - $h) . '#' unless $i % 23 and print "\e[4242;1H\n\e[40m\e[37m#                                                                              #";
    ($i + 13) % 23 ? '???' : abs $x - $h < 6 || (last);
    print "\e[$yy;${x}H\e[41m\e[37m\@";
}
ReadMode(1);
