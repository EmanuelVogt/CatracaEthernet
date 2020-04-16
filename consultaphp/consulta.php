	<?php     
	ini_set('display_errors', 1);
	ini_set('display_startup_errors', 1);
	error_reporting(E_ALL);

    $tag = '00000000';
   
        $tag = $_GET['tag'];
    
    require_once 'Class/acesso.php';    
    $u = new Usuario; 
    $u->conectar("banco_tags","localhost","root","SJQYdEEXW1hBDW");

    global $pdo;
    //verificar se o cadastro já existe 
    $sql = $pdo->prepare("SELECT id_tags FROM tags WHERE tag_tags = :t");
    $sql->bindValue(":t", $tag);
    $sql->execute();
    if($sql->rowCount() > 0)
        { 

            echo "OPEN"; 
        }
        else 
        {  
            echo "CLOSE";
        }

    //acessa o metodo para ver se a tag possui registro
    /*if($u->libera_acesso($Tag)===false)
        {       //acessa a tag para guardar dados de acesso 
                echo "Acesso liberado, registro cadastrado!";
                $u->controla_acesso($Tag, $disp);
               
        }
        
        else
        {
            echo "Acesso negado, registro não cadastrado!";
        }*/  
?>
