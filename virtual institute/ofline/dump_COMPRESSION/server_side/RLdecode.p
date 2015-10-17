

$Nmax=10000;
eval "\$$1=\$2" while ($#ARGV >= 0) && $ARGV[0]=~ /^(\w+)=(.*)/ && shift ;
$Nmax *= 2 ; 
#
#// Inverse of compressor (run length) for a sparse file.
#// its usage was
#// usage: RLencode < filep.01.10000 > file.RLZ
#
#// Brute force decoder (and very ugly!):
#// reads in bits from the file and does a strcmp
#// with all strings in the list, until it gets a match
# usage: 
#  RLdecode.p < file.RLZ > file.decoded
#
# This decoder prints out an extra run of zeros at the end of the file.
# To get the original file of length N lines, use:
# head -10000 file.decoded > file.final.decoded

#
# This perl program uses the substitution  operator
#  s/^blah//  to snip "blah" from the front of the string.
#

# First, get the compressed bit string from stdin into $b
# and ensure there are no spaces in it.
@a = <> ; 
$b = join( '' , @a ) ;
$b =~ s/\s+//g ; 

#// maximum permitted run of zeroes.
#define RMAX 69

$o = "" ;
while(!($b eq "")) {
    if( $b =~ s/^1// )	        { $o=$o. "0\n"x69 ;}
    elsif( $b =~ s/^0000000// ) { $o=$o. "0\n"x0 ."1\n" ;}
    elsif( $b =~ s/^0000010// ) { $o=$o. "0\n"x1 ."1\n" ; }
    elsif( $b =~ s/^0000011// ) { $o=$o. "0\n"x2 ."1\n" ;}
    elsif( $b =~ s/^0001000// )     { $o=$o. "0\n"x3 ."1\n" ;}
    elsif( $b =~ s/^0001001// )     { $o=$o. "0\n"x4 ."1\n" ;}
    elsif( $b =~ s/^0001010// )     { $o=$o. "0\n"x5 ."1\n" ;}
    elsif( $b =~ s/^0001011// )     { $o=$o. "0\n"x6 ."1\n" ;}
    elsif( $b =~ s/^0001100// )     { $o=$o. "0\n"x7 ."1\n" ;}
    elsif( $b =~ s/^0001101// )     { $o=$o. "0\n"x8 ."1\n" ;}
    elsif( $b =~ s/^0001110// )     { $o=$o. "0\n"x9 ."1\n" ;}
    elsif( $b =~ s/^0001111// )     { $o=$o. "0\n"x10 ."1\n" ;}
    elsif( $b =~ s/^0010000// )     { $o=$o. "0\n"x11 ."1\n" ;}
    elsif( $b =~ s/^0010001// )     { $o=$o. "0\n"x12 ."1\n" ;}
    elsif( $b =~ s/^0010010// )     { $o=$o. "0\n"x13 ."1\n" ;}
    elsif( $b =~ s/^0010011// )     { $o=$o. "0\n"x14 ."1\n" ;}
    elsif( $b =~ s/^0010100// )     { $o=$o. "0\n"x15 ."1\n" ;}
    elsif( $b =~ s/^0010101// )     { $o=$o. "0\n"x16 ."1\n" ;}
    elsif( $b =~ s/^0010110// )     { $o=$o. "0\n"x17 ."1\n" ;}
    elsif( $b =~ s/^0010111// )     { $o=$o. "0\n"x18 ."1\n" ;}
    elsif( $b =~ s/^0011000// )     { $o=$o. "0\n"x19 ."1\n" ;}
    elsif( $b =~ s/^0011001// )     { $o=$o. "0\n"x20 ."1\n" ;}
    elsif( $b =~ s/^0011010// )     { $o=$o. "0\n"x21 ."1\n" ;}
    elsif( $b =~ s/^0011011// )     { $o=$o. "0\n"x22 ."1\n" ;}
    elsif( $b =~ s/^0011100// )     { $o=$o. "0\n"x23 ."1\n" ;}
    elsif( $b =~ s/^0011101// )     { $o=$o. "0\n"x24 ."1\n" ;}
    elsif( $b =~ s/^0011110// )     { $o=$o. "0\n"x25 ."1\n" ;}
    elsif( $b =~ s/^0011111// )     { $o=$o. "0\n"x26 ."1\n" ;}
    elsif( $b =~ s/^0100000// )     { $o=$o. "0\n"x27 ."1\n" ;}
    elsif( $b =~ s/^0100001// )     { $o=$o. "0\n"x28 ."1\n" ;}
    elsif( $b =~ s/^0100010// )     { $o=$o. "0\n"x29 ."1\n" ;}
    elsif( $b =~ s/^0100011// )     { $o=$o. "0\n"x30 ."1\n" ;}
    elsif( $b =~ s/^0100100// )     { $o=$o. "0\n"x31 ."1\n" ;}
    elsif( $b =~ s/^0100101// )     { $o=$o. "0\n"x32 ."1\n" ;}
    elsif( $b =~ s/^0100110// )     { $o=$o. "0\n"x33 ."1\n" ;}
    elsif( $b =~ s/^0100111// )     { $o=$o. "0\n"x34 ."1\n" ;}
    elsif( $b =~ s/^0101000// )     { $o=$o. "0\n"x35 ."1\n" ;}
    elsif( $b =~ s/^0101001// )     { $o=$o. "0\n"x36 ."1\n" ;}
    elsif( $b =~ s/^0101010// )     { $o=$o. "0\n"x37 ."1\n" ;}
    elsif( $b =~ s/^0101011// )     { $o=$o. "0\n"x38 ."1\n" ;}
    elsif( $b =~ s/^0101100// )     { $o=$o. "0\n"x39 ."1\n" ;}
    elsif( $b =~ s/^0101101// )     { $o=$o. "0\n"x40 ."1\n" ;}
    elsif( $b =~ s/^0101110// )     { $o=$o. "0\n"x41 ."1\n" ;}
    elsif( $b =~ s/^0101111// )     { $o=$o. "0\n"x42 ."1\n" ;}
    elsif( $b =~ s/^0110000// )     { $o=$o. "0\n"x43 ."1\n" ;}
    elsif( $b =~ s/^0110001// )     { $o=$o. "0\n"x44 ."1\n" ;}
    elsif( $b =~ s/^0110010// )     { $o=$o. "0\n"x45 ."1\n" ;}
    elsif( $b =~ s/^0110011// )     { $o=$o. "0\n"x46 ."1\n" ;}
    elsif( $b =~ s/^0110100// )     { $o=$o. "0\n"x47 ."1\n" ;}
    elsif( $b =~ s/^0110101// )     { $o=$o. "0\n"x48 ."1\n" ;}
    elsif( $b =~ s/^0110110// )     { $o=$o. "0\n"x49 ."1\n" ;}
    elsif( $b =~ s/^0110111// )     { $o=$o. "0\n"x50 ."1\n" ;}
    elsif( $b =~ s/^0111000// )     { $o=$o. "0\n"x51 ."1\n" ;}
    elsif( $b =~ s/^0111001// )     { $o=$o. "0\n"x52 ."1\n" ;}
    elsif( $b =~ s/^0111010// )     { $o=$o. "0\n"x53 ."1\n" ;}
    elsif( $b =~ s/^0111011// )     { $o=$o. "0\n"x54 ."1\n" ;}
    elsif( $b =~ s/^0111100// )     { $o=$o. "0\n"x55 ."1\n" ;}
    elsif( $b =~ s/^0111101// )     { $o=$o. "0\n"x56 ."1\n" ;}
    elsif( $b =~ s/^0111110// )     { $o=$o. "0\n"x57 ."1\n" ;}
    elsif( $b =~ s/^0111111// )     { $o=$o. "0\n"x58 ."1\n" ;}
    elsif( $b =~ s/^00001000// )   { $o=$o. "0\n"x59 ."1\n" ;}
    elsif( $b =~ s/^00001001// )   { $o=$o. "0\n"x60 ."1\n" ;}
    elsif( $b =~ s/^00001010// )   { $o=$o. "0\n"x61 ."1\n" ;}
    elsif( $b =~ s/^00001011// )   { $o=$o. "0\n"x62 ."1\n" ;}
    elsif( $b =~ s/^00001100// )   { $o=$o. "0\n"x63 ."1\n" ;}
    elsif( $b =~ s/^00001101// )   { $o=$o. "0\n"x64 ."1\n" ;}
    elsif( $b =~ s/^00001110// )   { $o=$o. "0\n"x65 ."1\n" ;}
    elsif( $b =~ s/^00001111// )   { $o=$o. "0\n"x66 ."1\n" ;}
    elsif( $b =~ s/^00000010// )   { $o=$o. "0\n"x67 ."1\n" ;}
    elsif( $b =~ s/^00000011// )   { $o=$o. "0\n"x68 ."1\n" ;}
    else { print STDERR "ERROR!!!"; }
}
## // NB the outcome "69" is a string of 68 zeroes AND a zero, not a one.
$o = substr( $o, 0,$Nmax) if($Nmax) ; # strip off the top 10000 lines for printing
print $o;
