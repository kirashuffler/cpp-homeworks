#include <iostream>

#define SIZE 100

using namespace std;

//шаблон узла дерева
template <class TreeNode> class BinTreeNode
{
protected:
	//информация в узле дерева
	TreeNode info;
public:
	//правый, левый потомок и родитель
	BinTreeNode* Left;
	BinTreeNode* Right;
	BinTreeNode* Parent;

	BinTreeNode()
	{
		Left = NULL;
		Right = NULL;
		Parent = NULL;
	}

	//вывод элемента
	void print()
	{
		if(info!=NULL) cout << info;
	}
	//запись информации в узел дерева и его возврат при необходимости
	void SetInfo(TreeNode value) {info = value;}
	TreeNode GetInfo() {return info;}
};


//шаблон бинарного дерева
template <class TreeNode> class BinTree
{
public:
	BinTreeNode<TreeNode>* Root;
	BinTree()
	{
		Root = NULL;
	}
    BinTreeNode<TreeNode>* Min(BinTreeNode<TreeNode>* Node){
        if (Node->Left == NULL)
            return Node;
        return Min(Node->Left);
    }

    BinTreeNode<TreeNode>* Next(BinTreeNode<TreeNode>* Node){
        if (Node->Right != NULL)
            return Min(Node->Right);
        BinTreeNode<TreeNode>* Res = Node->Parent;
        while(Res != NULL && Node == Res->Right){
            Node = Res;
            Res = Res->Parent;
        }
        return Res;
    }

	//добавить узел
	void Add(TreeNode NewNode)
	{
		//нет ни одного узла - пишем его в корень
		if(Root==NULL)
		{
			Root = new BinTreeNode<TreeNode>();
			Root->SetInfo(NewNode);
			return;
		}
		//если узлы есть, ищем место для нового элемента - здесь итеративное решение (сделать рекурсивное)
		BinTreeNode<TreeNode>* Current = Root;
		while(Current!=NULL)
		{
			//текущий элемент больше вставляемого - идём влево по дереву
			if(Current->GetInfo() > NewNode)
			{
				if(Current->Left!=NULL)
				{
					Current = Current->Left;
					//cout<<Current->GetInfo()<<": Going to the left node\n"; char c; cin>>c;
					continue;
				}
				Current->Left = new BinTreeNode<TreeNode>();
				Current->Left->Parent = Current;
				Current->Left->SetInfo(NewNode);
				//cout<<"Setting Node\n";

				break;
			}
			//обратная ситуация - идём вправо
			if(Current->GetInfo() < NewNode)
			{
				if(Current->Right!=NULL)
				{
					Current = Current->Right;
					//cout<<Current->GetInfo()<<": Going to the right node\n";char c; cin>>c;
					continue;
				}
				Current->Right = new BinTreeNode<TreeNode>();
				Current->Right->Parent = Current;
				Current->Right->SetInfo(NewNode);
				//cout<<"Setting Node\n";

				break;
			}
			//в дереве уже есть такой элемент. Что делаем?
			if(Current->GetInfo() == NewNode)
			{
				//нашли совпадение имён
			}
		}
	}

	//поиск узла в дереве - повторяет логику добавления узла
	BinTreeNode<TreeNode>* Find(TreeNode T)
	{
		if(Root==NULL) return NULL;
		BinTreeNode<TreeNode>* Current = Root;
		while(Current!=NULL)
		{
			if(Current->GetInfo() < T)
			{
				Current = Current->Left;
				continue;
			}
			if(Current->GetInfo() > T)
			{
				Current = Current->Right;
				continue;
			}
			if(Current->GetInfo() == T)
				return Current;
		}
		return NULL;
	}

	//удаление узла из дерева
	void Remove(TreeNode T){
        BinTreeNode<TreeNode>* Current = Find(T);
        BinTreeNode<TreeNode>* p = Current->Parent;
        if (Current->Left == NULL && Current->Right == NULL){
            if(p->Left == Current)
                p->Left = NULL;
            if(p->Right == Current)
                p->Right = NULL;
        }
        else if(Current->Left == NULL || Current->Right == NULL){
            if (Current->Left == NULL)
                if (p->Left == Current)
                    p->Left = Current->Right;
                else{
                    p->Right = Current->Right;
                    Current->Right->Parent = p;
                }
            else{
                if(p->Left == Current)
                    p->Left = Current->Left;
                else
                    p->Right = Current->Left;
                Current->Left->Parent = p;
            }
        }else{
            BinTreeNode<TreeNode>* Successor = Next(Current);
            Current->SetInfo(Successor->GetInfo());
            if (Successor->Parent->Left == Successor){
                Successor->Parent->Left = Successor->Right;
                if(Successor->Right != NULL)
                    Successor->Right->Parent = Successor->Parent;
            }else{
                Successor->Parent->Right = Successor->Right;
                if (Successor->Right != NULL)
                    Successor->Right->Parent = Successor->Parent;
            }
        }
    }

	//применить некое действие, передаваемое как указатель на функцию, ко всем узлам в дереве
	void MakeAction(BinTreeNode<TreeNode>* Node, void (*f)(BinTreeNode<TreeNode>*))
	{
		if(Node!=NULL)
			f(Node);
		else
			MakeAction(Root, f);
		if(Node->Left!=NULL)
			MakeAction(Node->Left, f);
		if(Node->Right!=NULL)
			MakeAction(Node->Right, f);
	}
};

//распечатать всё дерево
template<class TreeNode> 
void print(BinTreeNode<TreeNode>* Node)
{
	if(Node!=NULL) cout<< Node->GetInfo();
}

class Student{
private:
    string Surname, Name, Patronymic, Group;
    unsigned Year = 0, Class = 0;
public:
    Student(){};
    Student(const Student& S){
        Surname = S.Surname;
        Name = S.Name;
        Patronymic = S.Patronymic;
        Year = S.Year;
        Class = S.Class;
        Group = S.Group;
    }

    Student(const string& surname, const string& name, const string& patronymic, unsigned year, unsigned  _class, const string& group){
        Surname = surname;
        Name = name;
        Patronymic = patronymic;
        Year = year;
        Class = _class;
        Group = group;
    }
    Student(const string& surname){
        Surname = surname;
    }
    Student(const string& surname,const string& group){
        Surname = surname;
        Group = group;
    }
    void operator = (const Student& S){
        Surname = S.Surname;
        Name = S.Name;
        Patronymic = S.Patronymic;
        Year = S.Year;
        Class = S.Class;
        Group = S.Group;
    }

    bool operator > (const Student& S){
        return (Surname > S.Surname || Group > S.Group);
    }
    
    bool operator < (const Student& S){
        return (Surname < S.Surname || Group < S.Group);
    }
    bool operator == (const Student& S){
        return (Surname == S.Surname || Group == Group);
    }
    friend ostream& operator << (ostream& stream, const Student& S){
        stream << S.Surname << ' ' << S.Name << ' ' << S.Patronymic << ' ' << S.Year << ' ' << S.Class << ' ' << S.Group << '\n';
        return stream;
    } 
};

int main()
{
    Student Azamat("Abzalov", "Azamat", "Ayratovich", 1997, 2, "KMBO-03-15");
    Student Sanya("Stroganov", "Alexandr", "Alexandrovich", 1997, 2, "KMBO-03-15");
    Student Erdny("Erendzhenov", "Erdny", "Nikolaevich", 1997, 2, "KMBO-03-15");
    Student Gosha("Bokovikov", "George", "Temurovich", 1997, 2, "KMBO-03-15");
    Student Maxim("Alekna", "Maxim", "Yurievich", 1997, 2, "KMBO-03-15");
    Student Senya("Fadyukov", "Arseniy", "Ilyich", 1997, 2, "KMBO-03-15");
    Student Anna("Novozhilova", "Anna", "Valyervna", 1997, 2, "KMBO-03-15");
    BinTree<Student> Students;
    Students.Add(Erdny);
    Students.Add(Azamat);
    Students.Add(Gosha);
    Students.Add(Sanya);
    Students.Add(Maxim);
    Students.Add(Anna);
    Students.Add(Senya);
    //Students.MakeAction(Students.Root,print);
    Students.Remove(Maxim);
    Students.MakeAction(Students.Root,print);
    return 0;
}

