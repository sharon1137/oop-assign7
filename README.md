# 2025 OOP Assignment #7
迷宮
### Description
延續作業5，執行方式皆與作業5相同

白色的牆：和作業5相同

藍色方塊靜止不動：作為障礙物(obstacle)

紅色方塊是玩家(player)：透過WASD移動

規則：
玩家從原點(0,0)（地圖左上角）出發，不可碰到藍色方塊，若碰到藍色方塊則重新回到原點，並且減去一條生命值（初始生命值為3），生命值為0則輸掉，並且輸出「You Lose！」。若玩家能在生命值>0時，移動到(19,19)（地圖右下角）則贏，並且輸出「You Win!」。

＊白色的牆不會減少生命值，只會阻礙移動。

![Flow Chart](images/oop-flow%20chart.png)
![UML](images/oop-UML.png)
