#include <stdio.h>
#include <locale.h>
#include <math.h>
//ВАРИАНТ 26
int main() {

    setlocale(LC_ALL, ".UTF8");

    //значения srv ram tmp (-1.0 заглушка, так же как и для массивов хранения показателей Q)
    float srv[] = { 43.7, 44.2, 44.7, -1.0, 51.1 };
    float ram[] = { 53.8, -1.0, 55.2, 53.2, 51.2 };
    float tmp[] = { 32.0, 31.3, 30.6, 35.2, 34.5 };

    //массивы для хранения производных показателей Q
    float q_srv[] = { -1.0, -1.0, -1.0, -1.0, -1.0 };
    float q_ram[] = { -1.0, -1.0, -1.0, -1.0, -1.0 };
    float q_tmp[] = { -1.0, -1.0, -1.0, -1.0, -1.0 };

    //массивы состояний компонентов(0 - НОРМА, 1 - РОСТ, 2 - СНИЖЕНИЕ)
    int s_srv[] = { 0, 0, 0, 0, 0 };
    int s_ram[] = { 0, 0, 0, 0, 0 };
    int s_tmp[] = { 0, 0, 0, 0, 0 };

    //константы для варианта 26
    int k = 2;
    float L = 1.5;
    int D = 20;

    int i;

    //блок расчета показателей Q
    for (i = k; i < 5; i++) {
        //расчет для SRV
        if (srv[i] != -1.0 && srv[i - k] != -1.0)
            q_srv[i] = pow(((srv[i] - srv[i - k]) / srv[i - k]), 2);
        //расчет для RAM
        if (ram[i] != -1.0 && ram[i - k] != -1.0)
            q_ram[i] = pow(((ram[i] - ram[i - k]) / ram[i - k]), 2);
        //расчет для TMP
        if (tmp[i] != -1.0 && tmp[i - k] != -1.0)
            q_tmp[i] = pow(((tmp[i] - tmp[i - k]) / tmp[i - k]), 2);
    }

    //блок анализа состояний компонентов
    for (i = 1; i < 5; i++) {

        //определение состояния для SRV
        if (q_srv[i] != -1.0 && q_srv[i - 1] != -1.0) {
            if (q_srv[i] > q_srv[i - 1])
                s_srv[i] = 1;
            else if (q_srv[i] < q_srv[i - 1])
                s_srv[i] = 2;
        }
        //определение состояния для RAM
        if (q_ram[i] != -1.0 && q_ram[i - 1] != -1.0) {
            if (q_ram[i] > q_ram[i - 1])
                s_ram[i] = 1;
            else if (q_ram[i] < q_ram[i - 1])
                s_ram[i] = 2;
        }
        //определение состояния для TMP
        if (q_tmp[i] != -1.0 && q_tmp[i - 1] != -1.0) {
            if (q_tmp[i] > q_tmp[i - 1])
                s_tmp[i] = 1;
            else if (q_tmp[i] < q_tmp[i - 1])
                s_tmp[i] = 2;
        }
    }

    for (i = 0; i < 5; i++) {
        printf("t = %d\n", i + 1);

        //перевод числовых значений состояний в текстовые строки для вывода
        char* srv_v = "Норма";
        if (s_srv[i] == 1)
            srv_v = "Рост";
        else if (s_srv[i] == 2)
            srv_v = "Снижение";

        char* ram_v = "Норма";
        if (s_ram[i] == 1)
            ram_v = "Рост";
        else if (s_ram[i] == 2)
            ram_v = "Снижение";

        char* tmp_v = "Норма";
        if (s_tmp[i] == 1)
            tmp_v = "Рост";
        else if (s_tmp[i] == 2)
            tmp_v = "Снижение";

        printf("SRV:  Q = %f Состояние = %s\n", q_srv[i], srv_v);
        printf("RAM: Q = %f Состояние = %s\n", q_ram[i], ram_v);
        printf("TMP: Q = %f Состояние = %s\n", q_tmp[i], tmp_v);

        //проверка инцидентов. если один компонент имеет рост
        //а другой одновременно снижение, то это инцидент
        int u = (s_srv[i] == 1 || s_ram[i] == 1 || s_tmp[i] == 1);
        int d = (s_srv[i] == 2 || s_ram[i] == 2 || s_tmp[i] == 2);

        if (u && d)
            printf("Инцидент\n");
        else
            printf("Инцидентов нет\n");
    }
    return 0;
}
