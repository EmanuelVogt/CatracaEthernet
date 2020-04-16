<?php
    require_once '../Class/crud_tags.php';
    $tags = new tags("banco_tags","localhost","root","SJQYdEEXW1hBDW");
?>

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <title>Cadastro</title>
    <link rel="stylesheet" href="../CSS/styleTags.css">
</head>
<body>
    <?php 
        if(isset($_POST['nome'])){
            if(isset($_GET['id_up']) && !empty($_GET['id_up'])){
                $id_up = addslashes($_GET['id_up']);
                $nome = addslashes($_POST['nome']);
                $cod = addslashes($_POST['cod']);
                $num = addslashes($_POST['num']);
                $tag = addslashes($_POST['tag']);
                if(!empty($nome) && !empty($cod) && !empty($tag)){
                    if(!$tags->atualizarDados($id_up, $nome, $cod, $num, $tag)){
                        ?>
                            <div class="aviso">
                                <h4>
                                <img src="cuidado.png" alt="">
                                     A tag já está cadastrada
                                </h4>
                            </div>
                        <?php
                    }
                    else{
                        ?>
                            <div class="aviso">
                                <h4>
                                    <img src="ok.png" alt="">
                                    Aualizada com sucesso!
                                </h4>
                            </div>
                        <?php
                    }
                }
                else{
                    ?>
                            <div class="aviso">
                            
                                <h4>
                                    <img src="cuidado.png" alt="">
                                    Preencha todos os campos
                                </h4>
                            </div>
                        <?php
                }

            }
            else{

                $nome = addslashes($_POST['nome']);
                $cod = addslashes($_POST['cod']);
                $num = addslashes($_POST['num']);
                $tag = addslashes($_POST['tag']);
                if(!empty($nome) && !empty($cod) && !empty($tag)){
                    if(!$tags->cadastrar($nome, $cod, $num, $tag)){
                        ?>
                            <div class="aviso">
                            
                                <h4>
                                    <img src="cuidado.png" alt="">
                                    A tag já está cadastrada
                                </h4>
                            </div>
                        <?php
                    }
                    else{
                        ?>
                            <div class="aviso">
                                <h4>
                                    <img src="ok.png" alt="">
                                    Cadastrada com sucesso!
                                </h4>
                            </div>
                        <?php
                    }
                }
                else{
                    ?>
                            <div class="aviso">
                                <h4>
                                <img src="cuidado.png" alt="">
                                    Preencha todos os campos
                                </h4>
                            </div>
                        <?php
                }
            }
        }
    ?>
    <?php 
        if(isset($_GET['id_up']))
        {
            $id_up = addslashes($_GET['id_up']);
            $res = $tags->buscarDadosTags($id_up);
        }
    ?>
    <section id="esquerda">
        <form method="POST">
            <h2>
                CADASTRAR PESSOA
            </h2>
            <label for="nome">NOME</label>
                <input type="text" name="nome" id="nome" value="<?php if(isset($res)){
                    echo $res['nome_tags'];
                }?>">
            <label for="cod">CÓDIGO</label>
                <input type="text" name="cod" id="cod" value="<?php if(isset($res)){
                    echo $res['cod_tags'];
                }?>"> 
            <label for="num">NÚMERO</label>
                <input type="text" name="num" id="num" value="<?php if(isset($res)){
                    echo $res['num_tags'];
                }?>">   
            <label for="tag">TAG</label>
                <input type="text" name="tag" id="tag" value="<?php if(isset($res)){
                    echo $res['tag_tags'];
                }?>">
            <input type="submit" value="<?php if(isset($res)){
                    echo "ATUALIZAR";
                } else { echo "CADASTRAR";}?>" >
        </form>
    </section>

    <!-- SEÇÃO DE EXIBIR OS DADOS NA DIREITA-->

    <section id="direita">
        <table>
                <a href="../pages/menu.php" id="voltar"> VOLTAR
                </a>
                <tr id="titulo">
                    <td>
                        NOME
                    </td>

                    <td>
                        CÓDIGO
                    </td>
                    <td>
                        NÚMERO
                    </td>

                    <td colspan="2">
                        TAG
                    </td>
                </tr>
            <?php
                $dados = array();
                $dados = $tags->buscarDados();
                if(count($dados) > 0){

                    for ($i=0; $i < count($dados); $i++){
                        echo "<tr>";
                        foreach ($dados[$i] as $k => $v){

                            if($k != "id_tags"){
                                echo "<td>$v</td>";
                            }
                        }
                        ?>
                            <td>
                                <a href="cadTags.php?id_up=<?php echo $dados[$i]['id_tags'];?>">EDITAR</a>
                                <a href="cadTags.php?id=<?php echo $dados[$i]['id_tags'];?>"> EXCLUIR </a>
                            </td>
                        <?php
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
                ?> 
    </section>
</body>
</html>
<?php 
    if(isset($_GET['id'])){
        $id = addslashes($_GET['id']); 
        $tags->excluir($id);
        header("location: cadTags.php");
    }
?>