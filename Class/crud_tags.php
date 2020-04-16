<?php
    Class tags{
        
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
        //função para capturar os dados
        public function buscarDados(){
            $res = array();
            $cmd = $this->pdo->query("SELECT * FROM tags ORDER BY nome_tags"); 
            $res = $cmd->fetchALL(PDO::FETCH_ASSOC);
            return $res;
        }           

        public function cadastrar($nome, $cod, $num, $tag){
            //verificar se já existe a tag
            $cmd = $this->pdo->prepare("SELECT id_tags from tags where tag_tags = :tag");
            $cmd->bindValue(":tag", $tag);
            $cmd->execute();
            if($cmd->rowCount() > 0){
                return false;
            }


            else{
                $cmd = $this->pdo->prepare("INSERT INTO tags(nome_tags, cod_tags, num_tags, tag_tags) 
                VALUES (:nome, :cod, :num, :tag)");
                $cmd->bindValue(":nome", $nome);
                $cmd->bindValue(":cod", $cod);
                $cmd->bindValue(":num", $num);
                $cmd->bindValue(":tag", $tag);
                $cmd->execute();
                return true;
            }
        }

        public function excluir($id){
            $cmd = $this->pdo->prepare("DELETE FROM tags WHERE id_tags = :id");
            $cmd->bindValue(":id", $id);
            $cmd->execute();
        }

        public function BuscarDadosTags($id){
            $res = array();
            $cmd = $this->pdo->prepare("SELECT * FROM tags WHERE id_tags = :id");
            $cmd->bindValue(":id", $id);
            $cmd->execute();
            $res = $cmd->fetch(PDO::FETCH_ASSOC);
            return $res;

        }
        
        public function atualizarDados($id, $nome, $cod, $num, $tag){
                $cmd = $this->pdo->prepare("UPDATE tags SET nome_tags = :nome, cod_tags = :cod, num_tags = :num, tag_tags = :tag WHERE id_tags = :id");
                $cmd->bindValue(":nome", $nome);
                $cmd->bindValue(":cod", $cod);
                $cmd->bindValue(":num", $num);
                $cmd->bindValue(":tag", $tag);
                $cmd->bindValue("id", $id);
                $cmd->execute();
                header("location: cadTags.php");
                return true; 

        }
    }
?>