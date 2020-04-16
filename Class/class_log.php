<?php 

    class class_log
    {
        private $pdo;
        public $msg = "";

        //metodo de conexão
        public function conection($name, $host, $user, $pass)
        {
            global $pdo;
            try{

                $this->pdo = new PDO("mysql:dbname=".$name.";host=".$host,$user,$pass);
            } catch (PDOExeption $e) {
               // $msg = $e->getMessege();
            }
        }


        public function login ($user, $pass)
        {
            global $pdo;
            $sql = $this->pdo->prepare("SELECT id_user FROM acess_login WHERE name_user = :user AND pass_user = :pass");
            $sql->bindValue(":user", $user);
            $sql->bindValue(":pass", $pass);
            $sql->execute();

            if($sql->rowCount() > 0)
            {
                //loga no sistema e inicia uma sessão
                $date = $sql->fetch();
                session_start();
                $_SESSION['id_user'] = $date['id_user'];
                return true; //logou com sucesso
            }
            else
            {
                return false; //login n efetuado
            }
        }

        public function cadAdmin($user, $cod, $pass)
        {
            global $pdo;
            //verificar se cadastro já existe
            $sql = $this->pdo->prepare("SELECT id_user FROM acess_login WHERE name_user = :user");
            $sql->bindValue(":user", $user);
            $sql->execute();
            if($sql->rowCount() > 0)
                {
                    return false; //se retornar false significa que o usuario já está cadastrado
                }
                else 
                {
                    $sql = $this->pdo->prepare("INSERT INTO acess_login (name_user, pass_user, cod_user) VALUES (:user, :cod, :pass)");
                    $sql->bindValue(":user", $user);
                    $sql->bindValue(":cod", $cod);
                    $sql->bindValue(":pass", $pass);
                    $sql->execute();
                    return true;
                }
            
        }
        public function buscaDados()
        {   
            $res = array();
            $sql = $this->pdo->query("SELECT * FROM tag_users ORDER BY name_user");
            $res = $sql->fetchAll(PDO::FETCH_ASSOC);
            return $res;
        }
        public function cadNewUser($name, $cod, $tag)
        {
            $sql = $this->pdo->prepare("SELECT id_tags FROM tag_users WHERE  tag_user = :tag");
            $sql->bindValue(":tag", $tag);
            $sql->execute();
                if($sql->rowCount() > 0)
                {
                    return false; //se retornar false significa que o usuario já está cadastrado
                }
                else 
                {
                    $sql = $this->pdo->prepare("INSERT INTO tag_users (name_user, cod_user, tag_user) VALUES (:name, :cod, :tag)");
                    $sql->bindValue(":name", $name);
                    $sql->bindValue(":cod", $cod);
                    $sql->bindValue(":tag", $tag);
                    $sql->execute();
                    return true;
                }
        }
        public function deleteUser($id)
        {
            $sql = $this->pdo->prepare("DELETE FROM tag_users WHERE id_tags = :id");
            $sql->bindValue(":id", $id);
            $sql->execute();
        }
        public function buscaDadosUser($id)
        {   $sql = array();
            $sql = $this->pdo->prepare("SELECT * FROM tag_users WHERE id_tags = :id");
            $sql->bindValue(":id", $id);
            $sql->execute();

            $res = $sql->fetch(PDO::FETCH_ASSOC);
            return $res;
        }
        public function attDados($id, $name, $cod, $tag)
        {
            $sql = $this->pdo->prepare("UPDATE tag_users SET name_user = :n, cod_user = :c,
            tag_user = :t WHERE id_tags = :id");
            $sql->bindValue(":n", $name);
            $sql->bindValue(":c", $cod);
            $sql->bindValue(":t", $tag);
            $sql->bindValue(":id", $id);
            $sql->execute();
            header("location: cadNewUser.php");
            return true;
                
        }
    }