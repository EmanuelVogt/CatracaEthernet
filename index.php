<?php
    require_once 'Class/class_log.php';
    $log = new class_log;
?>
<html>
    <head>
        <title>Acesso</title>
        <link rel="stylesheet" href="CSS/style.css">
    </head>
    <body id="index">
        <div id="body-form">
            <h1>Painel de login - NFC</h1>
            <form method= "POST">
                <input type="text" placeholder="Usuário" name="user" autocomplete="off"  required
    autofocus autocomplete="off">
                <input type="password" placeholder="Senha" name="pass" autocomplete="off">
                <input type="submit">
            </form>
        </div>
        <?php
            if(isset($_POST['user']))
            {
                $user = $_POST['user'];
                $pass = $_POST['pass'];
                
                if(!empty($user) && !empty($pass))
                {
                    $log->conection("login", "localhost", "root", "SJQYdEEXW1hBDW"); 
                    if($log->msg == "")
                    {
                         if($log->login($user, $pass))
                        {
                            echo "logou";
                            header("location: pages/menu.php");
                        }
                        else
                        {   ?>
                            <img src="./pages/aviso.png">
                            <div class="alert">
                                Informações incorretas.
                            </div>
                            <?php
                        }
                    }
                    else
                    {  
                        echo"Erro no banco: ".$log->msg;
                    }
                   
                }
                else
                {
                    ?>
                        
                            <div class="alert">
                            <img src="aviso.png">
                            Preencha todos os campos corretamente.
                            </div>
                            <?php
                }

            }
        ?>
    </body>
</html>