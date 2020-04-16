<?php

    class acesso{

        private $pdo;

        //função de conexão
        public function __construct($dbname, $host, $user, $senha){
            try{
                $this->pdo = new PDO("mysql:dbname=".$dbname.";host=".$host,$user,$senha);
    
            } catch(PDOExeption $e){
                echo "Erro com o banco de dados".$e->getMessage();
                exit();
                }
                catch(Exeption $e){
                echo "Erro com o banco de dados".$e->getMessage();
                exit();
                } 
        }

        public function acesso(){
            $res = array();
            $cmd = $this->pdo->query("SELECT * FROM acesso ORDER BY data"); 
            $res = $cmd->fetchALL(PDO::FETCH_ASSOC);
            return $res;
        }
        public function reseta(){
            $cmd = $this->pdo->prepare("TRUNCATE TABLE acesso");
            $cmd->execute();
        }
    }
    
?>