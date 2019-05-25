#include <gtest/gtest.h>
#include <QApplication>
#include <QTextStream>
#include "mainwindow.h"



TEST(GameWidget, Constructor){

    GameWidget w;
    EXPECT_EQ(w.getGenerations(),-1);
    EXPECT_EQ(w.getUniverseSize(), 50);
    EXPECT_EQ(w.getMasterColor(), QColor("#005500"));
    EXPECT_EQ(w.interval(), 300);
    EXPECT_EQ(w.cellNumber(),50);

}

TEST(GameWidget, SettersGetters){
    GameWidget w;
    w.setInterval(200);
    w.setCellNumber(100);
    w.setMasterColor("black");

    EXPECT_EQ(w.interval(),200);
    EXPECT_EQ(w.cellNumber(),100);
    EXPECT_EQ(w.getMasterColor(), QColor("black"));
}


TEST(GameWidget, Random){
     GameWidget g;
     g.random();
     int aliveCount = 0;
     for(int i = 0; i < g.getUniverseSize()*g.getUniverseSize(); i++)
         if(g.getUniverse()[i]) {
             aliveCount++;
             EXPECT_GE(g.getGeneration()[i], 0);
             EXPECT_LE(g.getGeneration()[i], 9);
         }

     EXPECT_LE(aliveCount, g.getUniverseSize()*g.getUniverseSize()/2);
     EXPECT_GE(aliveCount, g.getUniverseSize()*g.getUniverseSize()/4);
}

TEST(GameWidget, StartStopGame){
    GameWidget g;
    EXPECT_FALSE(g.timerState());

    g.startGame();
    EXPECT_TRUE(g.timerState());

    g.stopGame();
    EXPECT_FALSE(g.timerState());

}

TEST(Mainwindow, RulesChange){
    MainWindow w;
    bool* b = new bool[0,1,0,1,0,0,0,0,1];
    bool* s = new bool[1,0,0,1,0,1,0,0,0];
    w.getGame()->setRule(b, s);

    w.onComboboxChanged();

    EXPECT_NE(w.getGame()->getBorn(),b);
    EXPECT_NE(w.getGame()->getSurvive(),s);
    bool* prevBorn = w.getGame()->getBorn();
    bool* prevSurvive = w.getGame()->getSurvive();

    w.onComboboxChanged();
    EXPECT_NE(w.getGame()->getBorn(),prevBorn);
    EXPECT_NE(w.getGame()->getSurvive(),prevSurvive);
}


TEST(Mainwindow, SaveGame){
    MainWindow w;
    w.getGame()->random();

    w.saveFile("test.life");

    QFile file("test.life");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int sv;
    in >> sv;
    ASSERT_EQ(sv, w.getGame()->getUniverseSize());

    QString dump="";
    for(int k=0; k != sv; k++) {
        QString t;
        in >> t;
        dump.append(t+"\n");
    }

    int current = 0;
    bool* test = new bool[(sv+2)*(sv+2)];
    for(int k = 1; k <= sv; k++) {
        for(int j = 1; j <= sv; j++) {
            test[k*sv + j] = dump[current] == '*';
            current++;
            current++;
        }
        current++;
    }

    for(int k = 1; k <= sv; k++) {
        for(int j = 1; j <= sv; j++) {
            EXPECT_EQ(test[k*sv + j],w.getGame()->getUniverse()[k*sv + j]);
        }
    }

}



TEST(Pattern, selectPattern){
    MainWindow w;
    bool *current = new bool[36]{0, 0, 0, 0, 0, 0,
                                 0, 0, 1, 1, 0, 0,
                                 0, 1, 0, 0, 1, 0,
                                 0, 0, 1, 0, 1, 0,
                                 0, 0, 0, 1, 0, 0,
                                 0, 0, 0, 0, 0, 0};

    w.pattern.setCurrentPattern("1");
    int s = w.pattern.size;
    for (int j = 0; j<(s*s<36? s:6); j++) {
        for (int i = 0; i<(s*s<36? s:6); i++) {
            EXPECT_EQ(w.pattern.current[i*s+j], current[i*s+j]);
        }
    }

    w.pattern.setCurrentPattern("0");
    EXPECT_NE(w.pattern.current, current);

    w.getGame()->patternSelected(current,0);
    EXPECT_TRUE(w.getGame()->getPatternSelected());
}



int main(int argc,char*argv[])
{
    QApplication a(argc,argv);
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
