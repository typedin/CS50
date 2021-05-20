<!DOCTYPE html>

<html>
    <head>
        <title>hello</title>
    </head>
    <body>
        <?php if (!empty($_GET["name"])): ?>
            hello, <?= htmlspecialchars($_GET["name"]) ?>
        <?php else: ?>
            hello, world
        <?php endif ?>
            
            <?php print_r($_GET);
            ?>
    </body>
</html>
