<?php 

    class Cad {
        private $pdo;


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
    public function cadastrar($tag){
        
        $nule = "Undefined";
        $cmd = $this->pdo->prepare("INSERT INTO tags(nome_tags, cod_tags, num_tags, tag_tags) 
        VALUES (:nome, :cod, :num, :tag )");
        $cmd->bindValue(":nome", $nule);
        $cmd->bindValue(":cod", $nule);
        $cmd->bindValue(":num", $nule);
        $cmd->bindValue(":tag", $tag);
        $cmd->execute();
        return true;
    }
    public function excluir($tag){
        $cmd = $this->pdo->prepare("DELETE FROM tags WHERE tag_tags = :tag");
        $cmd->bindValue(":tag", $tag);
        $cmd->execute();
        return true;
    }

    public function acesso($tag){
        $res = array();
        $cmd = $this->pdo->prepare("SELECT * FROM tags WHERE tag_tags = :tag"); 
        $cmd->bindValue(":tag", $tag);
        $cmd->execute();
        $res = $cmd;

             while ($res = $cmd->fetch(PDO::FETCH_ASSOC)){
             $nome = $res['nome_tags'];
             $cod = $res['cod_tags'];
             $num = $res['num_tags'];
             $tag = $res['tag_tags'];
             $this->registra($nome, $cod, $num, $tag);
             }

        return true;
        
    }

    public function registra($nome, $cod, $num, $tag){
        $cmd = $this->pdo->prepare("INSERT INTO acesso(nome, tag, cod, num) 
        VALUES (:nome, :tag, :cod, :num)");
        $cmd->bindValue(":nome", $nome);
        $cmd->bindValue(":tag", $tag);
        $cmd->bindValue(":cod", $cod);
        $cmd->bindValue(":num", $num);
        $cmd->execute();
    }

}
    
?>