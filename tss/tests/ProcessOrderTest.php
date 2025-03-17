<?php

/**
 * Testare Structurală - processOrder.
 */
class ProcessOrderTest extends TestCase
{
    public function testProcessOrderProductNotFound(): void
    {
        $inventory = ['prod1' => 10, 'prod2' => 5];
        $result = $this->inventoryManager->processOrder($inventory, 'prod3', 2);

        $this->assertFalse($result['success']);
        $this->assertStringContainsString('nu există în stoc', $result['message']);
        $this->assertEquals($inventory, $result['updatedInventory']);
    }

    public function testProcessOrderInsufficientStock(): void
    {
        $inventory = ['prod1' => 10, 'prod2' => 5];
        $result = $this->inventoryManager->processOrder($inventory, 'prod2', 10);

        $this->assertFalse($result['success']);
        $this->assertStringContainsString('Stoc insuficient', $result['message']);
        $this->assertEquals($inventory, $result['updatedInventory']);
    }

    public function testProcessOrderSuccessful(): void
    {
        $inventory = ['prod1' => 10, 'prod2' => 5];
        $expectedInventory = ['prod1' => 5, 'prod2' => 5];

        $result = $this->inventoryManager->processOrder($inventory, 'prod1', 5);

        $this->assertTrue($result['success']);
        $this->assertStringContainsString('procesată cu succes', $result['message']);
        $this->assertEquals($expectedInventory, $result['updatedInventory']);
    }

    public function testProcessOrderZeroQuantity(): void
    {
        $inventory = ['prod1' => 10, 'prod2' => 5];
        $result = $this->inventoryManager->processOrder($inventory, 'prod1', 0);

        $this->assertTrue($result['success']);
        $this->assertEquals($inventory, $result['updatedInventory']);
    }
}
