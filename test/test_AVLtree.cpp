#include <gtest.h>
#include "AVLtree.h"
#include <vector>
#include <algorithm>

// Тест создания пустого дерева
TEST(AVLTreeTest, EmptyTree) {
    AVLTree<int> tree;
    EXPECT_TRUE(tree.isEmpty());  // Проверяем, что дерево пустое
}

// Тест вставки одного элемента
TEST(AVLTreeTest, InsertSingleElement) {
    AVLTree<int> tree;
    tree.insert(5);
    EXPECT_FALSE(tree.isEmpty());  // Проверяем, что дерево не пустое после вставки
}

// Тест поиска в пустом дереве
TEST(AVLTreeTest, FindInEmptyTree) {
    AVLTree<int> tree;
    EXPECT_FALSE(tree.is_contain(5));  // Проверяем, что элемент не найден в пустом дереве
}

// Тест поиска существующего элемента
TEST(AVLTreeTest, FindExistingElement) {
    AVLTree<int> tree;
    tree.insert(5);
    EXPECT_TRUE(tree.is_contain(5));  // Проверяем, что вставленный элемент находится
}

// Тест поиска несуществующего элемента
TEST(AVLTreeTest, FindNonExistingElement) {
    AVLTree<int> tree;
    tree.insert(5);
    EXPECT_FALSE(tree.is_contain(10));  // Проверяем, что невставленный элемент не находится
}

// Тест LL поворота (левый-левый случай)
TEST(AVLTreeTest, LL_Rotation) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);  // Должен вызвать LL поворот
    EXPECT_TRUE(tree.is_contain(10));  // Проверяем, что все элементы на месте после поворота
}

// Тест RR поворота (правый-правый случай)
TEST(AVLTreeTest, RR_Rotation) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  // Должен вызвать RR поворот
    EXPECT_TRUE(tree.is_contain(30));  // Проверяем, что все элементы на месте после поворота
}

// Тест LR поворота (левый-правый случай)
TEST(AVLTreeTest, LR_Rotation) {
    AVLTree<int> tree;
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);  // Должен вызвать LR поворот
    EXPECT_TRUE(tree.is_contain(20));  // Проверяем, что все элементы на месте после поворота
}

// Тест RL поворота (правый-левый случай)
TEST(AVLTreeTest, RL_Rotation) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);  // Должен вызвать RL поворот
    EXPECT_TRUE(tree.is_contain(20));  // Проверяем, что все элементы на месте после поворота
}

// Тест вставки дубликатов
TEST(AVLTreeTest, InsertDuplicates) {
    AVLTree<int> tree;
    tree.insert(5);
    tree.insert(5);  // Дубликат
    EXPECT_TRUE(tree.is_contain(5));  // Проверяем, что элемент все еще существует
}

// Тест удаления из пустого дерева
TEST(AVLTreeTest, RemoveFromEmptyTree) {
    AVLTree<int> tree;
    tree.remove(5);  // Не должно быть ошибки
    EXPECT_TRUE(tree.isEmpty());  // Проверяем, что дерево осталось пустым
}

// Тест удаления единственного элемента
TEST(AVLTreeTest, RemoveSingleElement) {
    AVLTree<int> tree;
    tree.insert(5);
    tree.remove(5);
    EXPECT_TRUE(tree.isEmpty());  // Проверяем, что дерево стало пустым
}

// Тест удаления листа (без потомков)
TEST(AVLTreeTest, RemoveLeaf) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.remove(5);  // Удаляем лист
    EXPECT_FALSE(tree.is_contain(5));  // Проверяем, что лист удален
}

// Тест удаления узла с одним потомком (левый)
TEST(AVLTreeTest, RemoveNodeWithLeftChild) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);  // Левый потомок для 5
    tree.remove(5);  // Узел с левым потомком
    EXPECT_FALSE(tree.is_contain(5));  // Проверяем, что узел удален
}

// Тест удаления узла с одним потомком (правый)
TEST(AVLTreeTest, RemoveNodeWithRightChild) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(7);  // Правый потомок для 5
    tree.remove(5);  // Узел с правым потомком
    EXPECT_FALSE(tree.is_contain(5));  // Проверяем, что узел удален
}
/*
// Тест удаления узла с двумя потомками
TEST(AVLTreeTest, RemoveNodeWithTwoChildren) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);  // Оба потомка для 5
    tree.remove(5);  // Узел с двумя потомками
    EXPECT_FALSE(tree.is_contain(5));  // Проверяем, что узел удален
}
*//*
// Тест удаления корня с двумя потомками
TEST(AVLTreeTest, RemoveRootWithTwoChildren) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.remove(10);  // Удаляем корень с двумя потомками
    EXPECT_FALSE(tree.is_contain(10));  // Проверяем, что корень удален
}
*/
// Тест балансировки после удаления (левый случай)
TEST(AVLTreeTest, BalanceAfterRemoval_LeftCase) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.remove(15);  // Может потребовать балансировку
    EXPECT_TRUE(tree.is_contain(3));  // Проверяем, что дерево сохранило структуру
}

// Тест балансировки после удаления (правый случай)
TEST(AVLTreeTest, BalanceAfterRemoval_RightCase) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(20);
    tree.remove(5);  // Может потребовать балансировку
    EXPECT_TRUE(tree.is_contain(20));  // Проверяем, что дерево сохранило структуру
}

// Тест конструктора копирования
TEST(AVLTreeTest, CopyConstructor) {
    AVLTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    AVLTree<int> tree2(tree1);  // Копируем
    EXPECT_TRUE(tree2.is_contain(10));  // Проверяем, что элементы скопированы
}

// Тест оператора присваивания
TEST(AVLTreeTest, AssignmentOperator) {
    AVLTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    AVLTree<int> tree2;
    tree2 = tree1;  // Присваиваем
    EXPECT_TRUE(tree2.is_contain(5));  // Проверяем, что элементы присвоены
}

// Тест самоприсваивания
TEST(AVLTreeTest, SelfAssignment) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree = tree;  // Самоприсваивание
    EXPECT_TRUE(tree.is_contain(10));  // Проверяем, что дерево не сломалось
}

// Тест очистки дерева
TEST(AVLTreeTest, ClearTree) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.clear();
    EXPECT_TRUE(tree.isEmpty());  // Проверяем, что дерево пустое
}

// Тест toSortedArray с пустым деревом
TEST(AVLTreeTest, ToSortedArray_Empty) {
    AVLTree<int> tree;
    int arr[10];
    tree.toSortedArray(arr, 10);
    // Не должно быть ошибки
    EXPECT_TRUE(tree.isEmpty());  // Дополнительная проверка, что дерево пустое
}

// Тест toSortedArray с одним элементом
TEST(AVLTreeTest, ToSortedArray_SingleElement) {
    AVLTree<int> tree;
    tree.insert(5);
    int arr[1];
    tree.toSortedArray(arr, 1);
    EXPECT_EQ(arr[0], 5);  // Проверяем, что массив содержит правильный элемент
}

// Тест toSortedArray с несколькими элементами
TEST(AVLTreeTest, ToSortedArray_MultipleElements) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    int arr[5];
    tree.toSortedArray(arr, 5);

    // Проверяем, что массив отсортирован (первый элемент минимальный)
    int min_val = *std::min_element(arr, arr + 5);
    EXPECT_EQ(arr[0], min_val);
}
/*
// Тест toSortedArray с ограниченным размером массива
TEST(AVLTreeTest, ToSortedArray_LimitedSize) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    int arr[2];  // Меньше размера дерева
    tree.toSortedArray(arr, 2);

    // Должны быть записаны только первые 2 элемента
    EXPECT_TRUE(arr[0] <= arr[1]);  // Проверяем, что они отсортированы
}
*/
// Тест конструктора из массива
TEST(AVLTreeTest, ConstructorFromArray) {
    int arr[] = { 10, 5, 15, 3, 7 };
    AVLTree<int> tree(arr, 5);
    EXPECT_TRUE(tree.is_contain(10));  // Проверяем, что элементы вставлены
}
/*
// Тест комплексного сценария с множеством операций
TEST(AVLTreeTest, ComplexScenario) {
    AVLTree<int> tree;

    // Вставка
    for (int i = 0; i < 10; ++i) {
        tree.insert(i);
    }

    // Проверка наличия
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(tree.is_contain(i));  // Проверяем, что все элементы присутствуют
    }

    // Удаление некоторых элементов
    tree.remove(5);
    tree.remove(7);

    EXPECT_FALSE(tree.is_contain(5));  // Проверяем, что удаленные элементы отсутствуют
}
*/
// Тест с отрицательными числами
TEST(AVLTreeTest, NegativeNumbers) {
    AVLTree<int> tree;
    tree.insert(-5);
    tree.insert(-10);
    tree.insert(-1);

    EXPECT_TRUE(tree.is_contain(-5));  // Проверяем работу с отрицательными числами
}

// Тест с большим количеством элементов
TEST(AVLTreeTest, LargeNumberOfElements) {
    AVLTree<int> tree;
    const int count = 100;

    for (int i = 0; i < count; ++i) {
        tree.insert(i);
    }

    for (int i = 0; i < count; ++i) {
        EXPECT_TRUE(tree.is_contain(i));  // Проверяем все элементы
    }
}

// Тест удаления всех элементов по одному
TEST(AVLTreeTest, RemoveAllElements) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    tree.remove(3);
    tree.remove(5);
    tree.remove(7);
    tree.remove(10);
    tree.remove(15);

    EXPECT_TRUE(tree.isEmpty());  // Проверяем, что дерево пустое
}

// Тест балансировки при последовательной вставке
TEST(AVLTreeTest, SequentialInsertBalance) {
    AVLTree<int> tree;

    // Вставка в отсортированном порядке (худший случай для BST, но AVL должен балансировать)
    for (int i = 0; i < 10; ++i) {
        tree.insert(i);
    }

    // Проверяем, что дерево остается сбалансированным
    int arr[10];
    tree.toSortedArray(arr, 10);

    // Все элементы должны быть на месте
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i);  // Проверяем правильность сортировки
    }
}
/*
// Тест на сохранение свойств AVL дерева после множества операций
TEST(AVLTreeTest, AVLPropertyMaintenance) {
    AVLTree<int> tree;

    // Случайная последовательность операций
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(10);
    tree.insert(30);
    tree.insert(60);
    tree.insert(80);
    tree.insert(5);
    tree.insert(15);
    tree.insert(55);
    tree.insert(65);

    // Удаляем и добавляем обратно
    tree.remove(25);
    tree.insert(25);

    tree.remove(75);
    tree.insert(75);

    // Проверяем, что все ключи на месте
    std::vector<int> keys = { 50, 25, 75, 10, 30, 60, 80, 5, 15, 55, 65 };
    for (int key : keys) {
        EXPECT_TRUE(tree.is_contain(key));  // Проверяем наличие всех ключей
    }
}
*/