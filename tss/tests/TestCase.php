<?php

use PHPUnit\Framework\TestCase as BaseTestCase;

abstract class TestCase extends BaseTestCase
{
    protected InventoryManager $inventoryManager;

    protected function setUp(): void
    {
        $this->inventoryManager = new InventoryManager();
    }
}
