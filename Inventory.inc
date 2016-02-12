<?php

define('ITEM_A', 2);
define('ITEM_B', 3);
define('ITEM_C', 1);
define('ITEM_D', 0);
define('ITEM_E', 0);

/**
 * base class to keep track of Inventoy.
 * using magic methods
 * the only custom method used for validation is getInventoryAmount
 */
class Inventory {

  private $A;
  private $B;
  private $C;
  private $D;
  private $E;
  
  public function __construct() {
     $this->A = ITEM_A;
     $this->B = ITEM_B;
     $this->C = ITEM_C;
     $this->D = ITEM_D;
     $this->E = ITEM_E;
  }
  
  public function __construct1($arga, $argb, $argc, $argd, $arge) {
     $this->A = $arga;
     $this->B = $argb;
     $this->C = $argc;
     $this->D = $argd;
     $this->E = $arge;
  }
  
  public function __destruct() {
    unset($this->A);
    unset($this->B);
    unset($this->C);
    unset($this->D);
    unset($this->E);
  } 
  
  function __get($propName) {
    $vars = array('A', 'B', 'C', 'D', 'E');
    if (in_array($propName, $vars)) {
      return $this->$propName;
    }
  }

  function __set($propName, $propValue) {
    $this->$propName -= $propValue;
  }

  public function getInventoryAmount() {
    return $this->A + $this->B + $this->C + $this->D + $this->E;
  }
}
?>
