<?php

/**
 * Testare Funcțională - calculateTotalPrice.
 */
class CalculateTotalPriceTest extends TestCase
{
    protected InventoryManager $inventoryManager;

    public function testCalculateTotalPriceWithZeroUnitPrice(): void
    {
        $this->expectException(InvalidArgumentException::class);
        $this->inventoryManager->calculateTotalPrice(0, 5);
    }

    public function testCalculateTotalPriceWithValidValues(): void
    {
        $result = $this->inventoryManager->calculateTotalPrice(10, 5);
        $this->assertEquals(50, $result);
    }

    public function testCalculateTotalPriceWithDiscount(): void
    {
        $result = $this->inventoryManager->calculateTotalPrice(10, 5, 20);
        $this->assertEquals(40, $result);
    }

    public function testCalculateTotalPriceWithBoundaryDiscount(): void
    {
        // Discount minim (0%)
        $result1 = $this->inventoryManager->calculateTotalPrice(10, 5, 0);
        $this->assertEquals(50, $result1);

        // Discount maxim (100%)
        $result2 = $this->inventoryManager->calculateTotalPrice(10, 5, 100);
        $this->assertEquals(0, $result2);
    }

    public function testCalculateTotalPriceWithZeroQuantity(): void
    {
        $result = $this->inventoryManager->calculateTotalPrice(10, 0);
        $this->assertEquals(0, $result);
    }

    public function testCalculateTotalPriceFailureWithInvalidValues(): void
    {
        $this->expectException(InvalidArgumentException::class);
        $this->inventoryManager->calculateTotalPrice(-10, 5);
    }

    public function testCalculateTotalPriceFailureWithInvalidDiscount(): void
    {
        $this->expectException(InvalidArgumentException::class);
        $this->inventoryManager->calculateTotalPrice(10, 5, 101);
    }

    public function testCalculateTotalPriceWithZeroDiscount(): void
    {
        $result = $this->inventoryManager->calculateTotalPrice(10, 5, 0);
        $this->assertEquals(50, $result);
    }
}
