echo "Updating configuration..."
echo "Running aclocal"
aclocal
echo "Running autoconf"
autoconf
echo "Running autoheader"
autoheader
echo "Running automake"
automake --add-missing --copy
