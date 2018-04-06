<?php
$cipher_text = $_POST['cipher_text'];
exec("vigapp/VigenereVictory {$cipher_text}", $ret);

echo json_encode($ret);
//echo "output: $output" . PHP_EOL;
//echo "ret: $ret" . PHP_EOL;
//echo var_dump($ret);
