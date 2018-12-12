use Term::ReadKey;
sub k {
    ReadKey(-1);
}
ReadMode(3);
sub rk {
    $i = shift();
    return (
        ($i > 22 and $i < 31) or ($i > 36 and $i < 53) or ($i > 67 and $i < 77) or ($i > 92 and $i < 102) or ($i > 110 and $i < 120) or
        ($i > 129 and $i < 144) or ($i > 154 and $i < 167) or ($i > 176 and $i < 193) or ($i > 207 and $i < 218) or ($i > 228 and $i < 238) or
        ($i > 246 and $i < 261) or ($i > 273 and $i < 283) or ($i > 292 and $i < 305) or ($i > 318 and $i < 330) or ($i > 337 and $i < 352) or
        ($i > 364 and $i < 376) or ($i > 387 and $i < 398) or ($i > 411 and $i < 422) or ($i > 428 and $i < 444) or ($i > 455 and $i < 467) or
        ($i > 477 and $i < 491) or ($i > 505 and $i < 515) or ($i > 527 and $i < 538) or ($i > 544 and $i < 561) or  ($i > 575 and $i < 584) or
        ($i > 595 and $i < 606) or ($i > 617 and $i < 627) or ($i > 632 and $i < 652)
    ) ? " " : "";
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
    $dx += int(rk($i) =~ / /g) * 2 - 1;
    $dx = $dx > 3 ? 3 : ($dx < -3 ? -3 : $dx);
    $x += $dx;
    last unless $x > 1 and $x < 80;
    $h = 20 + &$r(42) and print "\e[4242;1H\n\e[40m\e[37m#" . chr($HASH[$i / 23] ^ $h) x ($h - 5) . '          ' . chr($HASH[$i / 23] ^ $h) x (73 - $h) . '#' unless $i % 23 and print "\e[4242;1H\n\e[40m\e[37m#                                                                              #";
    ($i + 13) % 23 ? '???' : abs $x - $h < 6 || (last);
    print "\e[$yy;${x}H\e[41m\e[37m\@";
}
ReadMode(1);
