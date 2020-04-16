<?php
    require_once '../Class/class_log.php';
    $log = new class_log;
?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../CSS/style.css">
    <title></title>
</head>
<body>
        <h1>Cadastro de acesso ao painel</h1>
        
        <form method="POST" autocomplete="off">
            <input type="text" name="user" placeholder="Nome de usuário" pattern=".{0}|.{5,30}" required title="requerido de 5 a 30 caracteres" >
            <input type="text" name="cod" placeholder="Código do usuário" pattern=".{0}|.{5,15}" required title="requerido de 5 a 15 caracteres">
            <input type="password" name="pass" placeholder="Senha" pattern=".{0}|.{5,15}" required title="requerido de 5 a 15 caracteres">
            <input type="password" name="confPass"placeholder="Confirmar senha" minlength="5" maxlength="15">
            <input type="submit" value="Cadastrar">
            <a href="menu.php">VOLTAR</a>
            
        </form>

</body>
</html>
<?php 
    require_once '../Class/class_log.php';
    if (isset($_POST['user']))
    {  
        $user = addslashes($_POST['user']);
        $cod = addslashes($_POST['cod']);
        $pass = addslashes($_POST['pass']);
        //verificar se algum campo está vazio está vazio 
        if(!empty($user) && !empty($cod) && !empty($pass)) 
        {
            $log->conection("login", "localhost", "root", "SJQYdEEXW1hBDW"); 
            if ($log->cadAdmin($user, $cod, $pass))
            {
                ?>  

                    <div class="alert">
                        novo usuário do painel cadastrado com sucesso.
                    </div>
                <?php
            }
            else
            {
                ?>
                    <div class="alert">
                    <img src="aviso.png">
                        Esse usuario já possui registros no banco de dados.
                    </div>
                <?php
            }      
        }
        else 
        {
            ?>
                <div class="alert">
                <img src="aviso.png">   
                    Preencha todos os campos.
                </div>
            <?php
        }
    }
?>