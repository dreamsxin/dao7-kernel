#!/usr/bin/env php
<?php

use GetOpt\GetOpt;
use GetOpt\Option;
use GetOpt\Command;
use GetOpt\ArgumentException;

require_once __DIR__ . DIRECTORY_SEPARATOR . 'Dao7'. DIRECTORY_SEPARATOR. 'Loader.php';
Dao7\Loader::register();

define('NAME', 'Dao7');
define('VERSION', '1.0-alpha');

$getOpt = new GetOpt();

// define common options
$getOpt->addOptions([
	Option::create(null, 'version', GetOpt::NO_ARGUMENT)->setDescription('Show version information and quit'),
	Option::create('?', 'help', GetOpt::NO_ARGUMENT)->setDescription('Show this help and quit'),
]);

// add commands
$getOpt->addCommand(new Dao7\ClassCommand());

// process arguments and catch user errors
try {
	$getOpt->process();
} catch (ArgumentException $exception) {
	file_put_contents('php://stderr', $exception->getMessage() . PHP_EOL);
	echo PHP_EOL . $getOpt->getHelpText();
	exit;
}

// show version and quit
if ($getOpt->getOption('version')) {
	echo sprintf('%s: %s' . PHP_EOL, NAME, VERSION);
	exit;
}

// show help and quit
$command = $getOpt->getCommand();
if (!$command || $getOpt->getOption('help')) {
	echo $getOpt->getHelpText();
	exit;
}

// call the requested command
call_user_func($command->handler(), $getOpt);
