<?php
$cipher_text = $_POST['cipher_text'];
exec("vigapp/VigenereVictory {$cipher_text}", $ret);
echo json_encode($ret);

