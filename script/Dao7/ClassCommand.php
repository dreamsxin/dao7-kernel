<?php

namespace Dao7;

use GetOpt\Command;
use GetOpt\GetOpt;
use GetOpt\Option;
use GetOpt\Operand;

class ClassCommand extends Command
{
	public function __construct()
	{
		parent::__construct('class', [$this, 'handle']);

		$this->addOptions([
			Option::create(null, 'namespace', GetOpt::NO_ARGUMENT)->setDescription('Defining namespaces ')
		]);

		$this->addOperands([
			Operand::create('classname', Operand::REQUIRED)
		]);
		
	}
	
	public function handle(GetOpt $getOpt)
	{
		$classname = $getOpt->getOperand('classname');
		if ($getOpt->getOption('namespace')) {
		}
	} 
}

