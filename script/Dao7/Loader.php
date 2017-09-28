<?php

namespace Dao7;

/**
 * Class Loader
 * Loads classes when the composer autoloader is not installed
 *
 * @package Zephir
 */
class Loader
{
    /**
     * Register autoload
     */
    public static function register()
    {
        spl_autoload_register(array(__CLASS__, 'autoload'));
    }

    /**
     * @param string $className
     */
    public static function autoload($className)
    {
		$tmpname = str_replace('\\', DIRECTORY_SEPARATOR, $className);
        $filename = dirname(__DIR__). DIRECTORY_SEPARATOR . $tmpname . '.php';

        if (file_exists($filename)) {
            require $filename;
        }
    }
}