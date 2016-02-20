<?php

define('ITEM_A', 150);
define('ITEM_B', 150);
define('ITEM_C', 100);
define('ITEM_D', 100);
define('ITEM_E', 200);

/**
 * 
 * Base Inventory class.
 */
class Inventory {
  
  private $inventory;
  
  // Constructor:
  public function __construct() {     
     $this->inventory = $this->getSplFixedArray();
     $this->inventory = array('A' => ITEM_A,
       'B' => ITEM_B,
       'C' => ITEM_C,
       'D' => ITEM_D,
       'E' => ITEM_E);
  }
  
  public function __destruct() {
    unset($this->inventory);
  } 
  
  /**
   * 
   * @param string $propName
   * @return int
   */
  function __get($propName) {
    $vars = array('A', 'B', 'C', 'D', 'E');
    if (in_array($propName, $vars)) {
      return $this->inventory[$propName];
    }
  }

  /**
   * 
   * @param string $propName
   * @param int $propValue
   */
  function __set($propName, $propValue) {
    $this->inventory[$propName] -= $propValue;
  }

  /**
   * custom method to monitor integral state of inventory
   * 
   * @return int
   */ 
  public function getInventoryAmount() {
    return $this->inventory['A'] + $this->inventory['B'] + $this->inventory['C'] + 
      $this->inventory['D'] + $this->inventory['E'];
  }

  /**
   * custom method uses SplFixedArray
   * 
   * @return \SplFixedArray
   */
  private function getSplFixedArray() {
    return new  SplFixedArray(INVENTORY_SIZE);
  }

}
?>
