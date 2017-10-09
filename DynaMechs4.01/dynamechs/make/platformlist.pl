#!/usr/bin/perl

opendir(DIR, "make") || die "can't opendir make: $!";
@platforms = readdir(DIR);
closedir(DIR);

foreach (@platforms) {
  if (/^make\.platform\./) {
    s/make\.platform\.//;
    print " " . $_;
  }
}
