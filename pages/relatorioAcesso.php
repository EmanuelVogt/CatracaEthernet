<?php
    require_once '../Class/class_acesso.php';
    $acesso = new acesso("banco_tags","localhost","root","SJQYdEEXW1hBDW");
?>
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../CSS/style_acesso.css">
    <title>Document</title>
</head>
<body>
        <form action="relatorioAcesso.php" method="GET">
            <input type="text" name="res" id="res" placeholder="Digite OK">
            <input type="submit" value="RESET"/>
        </form>

    <table>
                <a href="../pages/menu.php" id="voltar"> VOLTAR
                </a>
                <tr id="titulo">
                    <td>
                        NOME
                    </td>
                    <td>
                        TAG
                    </td>

                    <td>
                        CÓDIGO
                    </td>

                    <td>
                        NÚMERO
                    </td>

                    <td>
                        DADA | HORA
                    </td>
                </tr>
            <?php
                $dados = array();
                $dados = $acesso->acesso();

                if(count($dados) > 0){

                    for ($i=0; $i < count($dados); $i++){
                        echo "<tr>";
                        foreach ($dados[$i] as $k => $v){

                            if($k != "id"){
                                echo "<td>$v</td>";
                            }
                        }
                        echo "<tr>";
                    }
                }
                else {

            ?>
            </tr>
        </table>
                        <div class="aviso">
                            <h4>
                                <img src="cuidado.png" alt="">
                                Sem registros no banco de dados
                            </h4>
                        </div>
                    <?php
                }
                if(isset($_GET['res'])){
                    $id = addslashes($_GET['res']);
                    if($id == "OK"){
                         $acesso->reseta();
                        header("location: relatorioAcesso.php");
                    }   
                   
                }
                ?> 
    </section>
</body>
</html>