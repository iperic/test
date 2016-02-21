<?php

include '../Inventory.inc';
include '../Orders.inc';
/**
 * Description of unitTest
 *
 * @author iperic
 */
class unitTest extends PHPUnit_Framework_TestCase{
   public function setUp(){ }
   public function tearDown(){ }

   public function testOneInventory() {
     $inv = new Inventory;
     $this->assertTrue($inv->A == ITEM_A);  
   }
   
   public function testTwoOrders() {
     $ord = new Orders;  
     $this->assertTrue((Orders::getZeroList()->A) ==0);  
   }    
}
