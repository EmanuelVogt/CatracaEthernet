<?php 

    class Usuario
    {
        public $pdo;
        public $msg = "";

        //conecta com o banco
        public function conectar($nome, $host, $usuario, $senha)
        {
            global $pdo;
            try{

                $pdo = new PDO("mysql:dbname=".$nome.";host=".$host,$usuario,$senha);
            } catch (PDOExeption $e) {
               // $msg = $e->getMessege();
            }
        }
    }
    
?>