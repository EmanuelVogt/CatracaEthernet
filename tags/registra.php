<?php  
    require_once 'Class/tags.php';    
    $tags = new Cad("banco_tags","localhost","root","SJQYdEEXW1hBDW");

    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

    $tag = '00000000';
    if(isset($_GET['tag']))
    {
        $tag = (string)$_GET['tag'];
        $tag = strtoupper($tag);

        if( $tags->acesso($tag) == true){
            echo "FEITO";
        }else{
            echo "FAIL";
        }
       
        
    }
?>