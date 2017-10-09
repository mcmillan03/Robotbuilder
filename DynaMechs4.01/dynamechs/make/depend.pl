#!/usr/bin/perl

sub parseOldDepends {
  my $inFile = shift(@_);
  my $outFile = shift(@_);
  my $dirtyOut = shift(@_);
  my @dirtyIn = split(" ", $dirtyOut);

  if (open(INFILE, $inFile)) {
  LINE: foreach (<INFILE>) {
      for ($ii = 0; $ii <= $#dirtyIn; $ii++) {
	if (m/.*$dirtyIn[$ii].*/) {
	  m/ (.*): (.*)/;
	  ($first, $second) = split(/ /, $2, 2);
	  if (!grep(/$first/, $dirtyOut)) {
	    $dirtyOut .= " " . $first;
	  }
	  next LINE;
	}
      }
      if ($_ ne "\n") {
	print OUTFILE $_;
      }
    }
    
    close(INFILE);
  }
  
  return $dirtyOut;
}



sub calcNewDepends {
  my $firstfile = shift(@_);
  my @files;
  push @files, $firstfile;
  my %depFiles;
  while ($#files >= 0) {
    $currfile = shift(@files);
#    print "currfile = $currfile \n";
    if ($depFiles{$currfile} != 1) {
      if (!$filePath{$currfile}) {
#	print "parsing $currfile \n";
	$filePath{$currfile} = "x";
	foreach (@includePaths) {
	  $checkfile = $_ . "/" . $currfile;
#	  print "checking $checkfile \n";
	  if (open(INFILE, $checkfile)) {
#	    print "opened file \n";
	    $filePath{$currfile} = $checkfile;
	    foreach (<INFILE>) {
	      if (m/^\s*\#\s*include\s*[<\"](.*)[>\"]/) {
		$parsedFiles{$currfile} .= $1 . " ";
#		print "found dep = $1 \n";
	      }
	    }
	    close(INFILE);
	    last;
	  }
	}
      }
#      print "parsed deps = $parsedFiles{$currfile} \n";
      if ($parsedFiles{$currfile}) {
	push @files, split(" ",$parsedFiles{$currfile});
      }
#      print "files = " . join(" ",@files) . "\n";
      if ($currfile ne $firstfile) {
	$depFiles{$currfile} = 1;
      }
    }
  }

#  print "deps = " . join(" ",keys(%depFiles)) . "\n";
  my @deps;
  push @deps, $firstfile;
  foreach (keys %depFiles) {
    if ($filePath{$_} ne "x") {
      push @deps, $filePath{$_};
    }
  }
  return @deps;
}


##############################################################################

$inFile = shift(@ARGV);
$outFile = $inFile . ".tmp";

unlink $outFile;
open(OUTFILE, ">$outFile") 
  || die "$0 unable to open output file: $outFile";

#print "ARGV= @ARGV \n";

($dirtyIn, $allArgs) = split(" -- ", join(" ",@ARGV));

#print "dirtyIn= $dirtyIn \n";

push @includePaths, ".";
foreach (split(" ", $allArgs)) {
  if (/^-I(.*)/) {
    next if (/.*\:.*/);
    push @includePaths, $1;
  }
}

#print "inc paths = " . join(" ",@includePaths) . "\n";

$dirtyOut = parseOldDepends($inFile, $outFile, $dirtyIn);

#print "dirtyOut= $dirtyOut \n";
#print "cxxArgs= $cxxArgs \n";

foreach (split(" ",$dirtyOut)) {
  if (m/\.cpp$/ || m/\.c$/) {
    $compileList .= " " . $_;
  }
}

#print "compileList= $compileList \n";


$filler = $inFile;
$filler =~ s|(.*/)[^/ ]*\.d$|\1|;
$filler = $inFile . " " . $filler;
foreach (split(" ",$compileList)) {
#  print "compile = $_ \n";
  @deps = calcNewDepends($_);
  s|.*/([^/ ]*)\.[^/ ]*$|\1|;
  print OUTFILE "$filler" . $_ . ".o: @deps \n";
}

close(OUTFILE);

if (stat($outFile) ne "") {
  rename($outFile, $inFile) 
    || die "$0 unable to rename $outFile to $inFile";
}


