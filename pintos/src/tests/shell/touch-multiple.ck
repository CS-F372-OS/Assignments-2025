# -*- perl -*-
use strict;
use warnings;
use tests::tests;

check_expected([<<'EOF']);
touch: created testfile1.txt
touch: created testfile2.txt
touch: updated testfile1.txt
EOF
pass;
