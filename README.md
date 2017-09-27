Get Started
-----------

### Linux/Unix/Mac

On a Unix-based platform you can easily compile and install the extension from sources.

#### Requirements
Prerequisite packages are:

* PHP 7.0.x development resources
* GCC compiler (Linux/Solaris) or Xcode (Mac)

Compilation
-----------

Follow these instructions to generate a binary extension for your platform:

```bash
git clone git://github.com/dreamsxin/dao7-kernel.git
cd dao7-kernel/

./skel.sh --extname=Demo

cd demo/ext

phpize
./configure
make -j4
sudo make install
```

Tests
-----
```php
php -r "echo Demo\Version::get().PHP_EOL;"
```

License
-------
Dao7 kernel is open source software licensed under the New BSD License.