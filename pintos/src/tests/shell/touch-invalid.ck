# -*- perl -*-
use strict;
use warnings;
use tests::tests;

check_expected([<<'EOF']);
touch: created validfile.txt
touch: cannot create '/invalid/path/file.txt'
EOF
pass;
