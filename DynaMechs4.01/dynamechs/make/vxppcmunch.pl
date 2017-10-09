#!/usr/bin/perl

#print "$#ARGV args\n";
while ($#ARGV >= 0) {
  $arg = shift(@ARGV);
  #print "arg = $arg \n";
  next if ($arg =~ /^-L/);
  next if ($arg =~ /^-l/);
  if ($arg eq "-o") {
    $arg = shift(@ARGV);
    $outfile = $arg;
    next;
  }
  $infiles .= " " . $arg;
}

($munchcfile,$junk) = split(" ",$infiles);
$munchcfile =~ s|(.*/)[^/]*$|\1|;
#$tmplinkfile = $munchcfile . "tmp.o";
$munchofile = $munchcfile . "ctdt.o";
$munchcfile .= "ctdt.c";

unlink $munchcfile;
unlink $munchofile;
#unlink $tmplinkfile;
#system("ccppc -Wl,-Ur -o $tmplinkfile $infiles");
#system("nmppc $tmplinkfile | wtxtcl /usr/wind2/host/src/hutils/munch.tcl -asm ppc > $munchcfile");
system("nmppc $infiles | wtxtcl /usr/wind2/host/src/hutils/munch.tcl -asm ppc > $munchcfile");
system("ccppc -c $munchcfile -o $munchofile");
system("ccppc -Wl,-Ur -o $outfile $infiles $munchofile");
unlink $munchcfile;
unlink $munchofile;
#unlink $tmplinkfile;

