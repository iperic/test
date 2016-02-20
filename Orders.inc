<?php

/**
 * base Order class.
 * 
 */
class Orders {
  private $orders = array();
  //
  function addLine($arg) {
    $order_line = $this->initiateNewLine();
    $order_line['headerId'] = $arg['headerId'];

    foreach ($arg['data'] as $key => $value) {
      $order_line['data']['order'][$key] = $value[0];
      $order_line['data']['allocated'][$key] = $value[1];
      $order_line['data']['backorder'][$key] = $value[2];
    }
    $order_line['headerId'] = $arg['headerId'];
    $this->orders[] = $order_line;
  }

  //in form of output create each line and filled it with 0
  private function initiateNewLine($zero_array) {
    $zero_array = self::getZeroList();  
    return array('headerId' => 0, 
      'data' => array('order' => $zero_array,
      'allocated' => $zero_array,
      'backorder' => $zero_array)); 
  }
  
  //print json 
  public function printOrders() {
    echo json_encode($this->orders);
  }
  
  /**
   * magic method __toString()
   * 
   * @return string
   */
  public function __toString(){
    foreach($this->orders as $key => $value) {
       $ord =  array_values($value['data']['order']);
       $alloc = array_values($value['data']['allocated']);
       $back = array_values($value['data']['backorder']);
       $return_str .= $value['headerId'] . ': ' . implode(',', $ord) . ' :: ' . implode(',', $alloc) . ' :: ' . implode(',', $back) . "\r\n";
    }
    return $return_str;
  }
  
   /**
   * 
   * @return array
   */
  public static function getZeroList() {
     return array('A'=> 0, 'B'=> 0, 'C'=> 0, 'D'=> 0, 'E'=> 0);
  }
}
?>

