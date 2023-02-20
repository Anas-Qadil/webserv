#!/usr/bin/php

<?php

// Get the file data
$file_data = file_get_contents($_FILES["file"]["tmp_name"]);

// Get the file name
$file_name = $_FILES["file"]["name"];

// Create the file in the specified path
$path = "/Users/aaitoual/Desktop/Web_server/content";
$file_path = implode("/", [$path, $file_name]);
$file = fopen($file_path, "wb");
fwrite($file, $file_data);
fclose($file);

// Print a message to confirm that the file was created
echo "Content-type: text/html\n\n";
echo "File '{$file_name}' successfully created in {$path}";

?>
