#!/usr/bin/php

 <?php

  include 'Inventory.inc';
  include 'Orders.inc';

/**
 * TEST DATA
 *   
  $json = '[{"Header": 1, "Lines": [{"Product": "A", "Quantity": 1},{"Product": "C", "Quantity": 1}]},
{"Header": 2, "Lines": [{"Product": "E", "Quantity": 5}]},
{"Header": 3, "Lines": [{"Product": "D", "Quantity": 4}]},
{"Header": 4, "Lines": [{"Product": "A", "Quantity": 1},{"Product": "C", "Quantity": 1}]},
{"Header": 5, "Lines": [{"Product": "B", "Quantity": 3}]},
{"Header": 6, "Lines": [{"Product": "D", "Quantity": 4}]}]';
*/

print "Please enter your Input in JSON format: \r\n";

$fp = fopen('php://stdin', 'r');

$inventory = new Inventory;
$orders = new Orders;

//taking input from the console
while (1) {
$last_line = false;
$message = '';
  //take case of input line larger than 1024
  while (!$last_line) {
    $next_line = trim(fgets($fp, 1024));
    if (substr($next_line, -1) == "]") { 
      $last_line = true;
    } 
    $message .= $next_line;
  } 

  // JSON
  try {
    $input = json_decode($message);
    if (is_null($input)) {
        throw new Exception('Invalid JSON format!');
    }
  }
  catch(Exception $e) {
    // catch exceoption but allow a user to keep entering the data
    echo $e->getMessage();
  }

  foreach($input as $key => $line) {
    $order_line = array();
    $header = (string)$line->Header;
    $amount = $inventory->getInventoryAmount();
      if ($amount == 0) {
        echo $orders;
//      $orders->printOrders(); 
        fclose($fp);
        exit(0);
      }    
    foreach($line->Lines as $key => $value) {
      //validate input rule about Qtys  
      if (!is_int($value->Quantity) || $value->Quantity < 0 || $value->Quantity > 5 ) {
        $order_line = NULL;
        continue;
      }

      $prod = $value->Product;
      $inv_value = $inventory->$prod;

      //determine acction and Qtys
      if ($inv_value >= $value->Quantity) {
        $inventory->$prod = $value->Quantity;
        $order = $value->Quantity;
        $allocated = $value->Quantity;
        $backorder = 0;
      }
      else {
        if ($inv_value > 0) {
          $inventory->$prod($inv_value);
        }
        $order = $value->Quantity;
        $allocated = $inv_value;
        $backorder = $value->Quantity - $inv_value;
      }
    //take case of multiple lines
    $order_line[$prod] = array($order, $allocated, $backorder);
   }
   $line = array('headerId' => $header, 'data' => $order_line);
   $orders->addLine($line);
   
   //after the prcessing, check the Inventory
   $amount = $inventory->getInventoryAmount();
   if ($amount == 0) {
     echo $orders;
//      $orders->printOrders(); 
     fclose($fp);
     exit(0);
   }   
  }
}

?>


