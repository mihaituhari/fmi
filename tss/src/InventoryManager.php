<?php

/**
 * Clasa care conține funcții pentru un backend PHP
 */
final class InventoryManager
{
    /**
     * Calculează prețul total al unui produs în funcție de cantitate și aplicând discount.
     *
     * - Funcție pentru testare funcțională
     * - Conține o condiție simplă și una compusă
     * - Conține instrucțiune repetitivă
     *
     * @param float $unitPrice Prețul unitar al produsului
     * @param int $quantity Cantitatea
     * @param int $discountPercentage Discount-ul aplicat (0-100)
     *
     * @return float Prețul total
     */
    public function calculateTotalPrice(float $unitPrice, int $quantity, int $discountPercentage = 0): float
    {
        // Validare parametri (condiție compusă)
        if ($unitPrice < 0 || $quantity < 0 || $discountPercentage < 0 || $discountPercentage > 100) {
            throw new InvalidArgumentException("Parametrii trebuie să fie pozitivi și discount-ul între 0 și 100");
        }

        $total = 0;

        // Instrucțiune repetitivă (for)
        for ($i = 0; $i < $quantity; $i++) {
            $total += $unitPrice;
        }

        // Condiție simplă
        if ($discountPercentage > 0) {
            $total *= (1 - $discountPercentage / 100);
        }

        return $total;
    }

    /**
     * Verifică dacă un produs este în stoc și actualizează stocul dacă se face o comandă.
     *
     * - Funcție pentru testare structurală
     * - Conține if cu else și if fără else
     * - Conține instrucțiune repetitivă (while)
     *
     * @param array<string,int> $inventory Stocul curent
     * @param string $productId ID-ul produsului
     * @param int $requestedQuantity Cantitatea solicitată
     *
     * @return array{success: bool, message: string, updatedInventory: array<string,int>} Stocul actualizat și un mesaj de status
     */
    public function processOrder(array $inventory, string $productId, int $requestedQuantity): array
    {
        $result = [
            'success' => false,
            'message' => '',
            'updatedInventory' => $inventory,
        ];

        // Verificăm dacă produsul există în inventar
        if (!isset($inventory[$productId])) {
            $result['message'] = "Produsul cu ID-ul {$productId} nu există în stoc";

            return $result;
        }

        $availableQuantity = $inventory[$productId];

        // Verificăm dacă este suficient stoc
        if ($availableQuantity >= $requestedQuantity) {
            // Actualizăm stocul - instrucțiune repetitivă (while)
            $updated = 0;

            while ($updated < $requestedQuantity) {
                $inventory[$productId]--;
                $updated++;
            }

            $result['success'] = true;
            $result['message'] = 'Comandă procesată cu succes';
            $result['updatedInventory'] = $inventory;
        } else {
            $result['message'] = "Stoc insuficient. Disponibil: {$availableQuantity}";
        }

        return $result;
    }
}
