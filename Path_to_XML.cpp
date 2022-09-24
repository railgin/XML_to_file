//Задание №3
//
//Написать консольное приложение, экспортирующее заданный каталог в файл формата XML.
//
//Например, на вход задается строка вида
//"C:\WINDOWS\".
//Программа должна, начиная с этого каталога, вывести древовидную структуру
//всех подкаталогов в текстовый файл формата XML.Названия файлов в XML не выводить, только каталоги.
//Структура XML - на Ваше усмотрение, но она должна быть логичной.
//
//Условия :
//1) Предпочтительная целевая платформа - Windows.
//2) Можно использовать любые средства стандартной библиотеки C / C++, WINAPI, Shlwapi.dll и ShFolder.dll, STL.
//3) XML создать не используя парсер, выводом строк непосредственно в файл.
//4) Формируемый XML должен соответствовать стандарту.
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

string converter(const string& str)
{
	string tmp1;
	tmp1.resize(0);
	int i = str.size() - 1;
	do
	{
		tmp1.push_back(str[i]);
		i--;
	} while (str[i] != '\\');

	string tmp2;
	tmp2.resize(0);
	for (int i = 0; i < tmp1.size(); i++)
	{
		tmp2.push_back(tmp1[tmp1.size() - i - 1]);
	}
	return tmp2;
}

string PathToString(const filesystem::path& file_path)//эти два метода для вывода либо с последними элементами директорий(последняя папка 
													//или файл в ней), либо без них
{
	string str;
	str = file_path.string();
	return str;
}

string DirToString(const filesystem::path& file_dir)
{

	string str;
	filesystem::path temp = file_dir.parent_path();
	str = temp.string();
	return str;
}

//void XMLtoConsole(const string &ent_str , int counter, int previous_depth, int local_parent_depth, int parent_counter)
//{
//	vector<int> parent_indexs;
//	vector<filesystem::path> par_adresses;
//	vector<int> par_depth;
//	vector<string> par_adresses1;
//	
//	parent_indexs.resize(0);
//	par_depth.resize(0);
//
//	filesystem::path parent_adress;
//	filesystem::path prev_adress;
//
//	cout << "<xml version = '1.0' encoding = windows-1251" << '>' << endl;
//	cout << '<' << ent_str << '>' << endl;
//
//	string str_par_adress;
//
//
//
//	for (auto i = filesystem::recursive_directory_iterator(ent_str); i != filesystem::recursive_directory_iterator(); ++i)
//	{
//		string str_path = PathToString(*i);
//		
//		//str_path = converter(str_path); //если хотим выводить только названия
//
//		for (int k = 0; (k < parent_indexs.size() - 1) && i.depth() < previous_depth; k++)
//		{
//			str_par_adress = PathToString(par_adresses[parent_indexs.size() - 1]);
//			cout << '\t' << string(local_parent_depth, '\t') << "</"
//				<< str_par_adress << '>' << endl;
//			if (parent_indexs.size() > 0)
//			{
//				parent_indexs.pop_back();
//				par_adresses.pop_back();
//				par_depth.pop_back();
//			}
//			parent_counter--;
//			local_parent_depth--;
//		}
//
//		if (i.depth() > previous_depth)
//		{
//			local_parent_depth = previous_depth;
//			//parent_counter = counter - 1;
//			parent_indexs.push_back(parent_counter);
//			parent_adress = prev_adress;
//			par_adresses.push_back(parent_adress);
//
//			par_depth.push_back(previous_depth);
//		}
//
//		cout << '\t' << string(i.depth(), '\t') << '<' << str_path << '>';
//
//		previous_depth = i.depth();
//		prev_adress = str_path;
//		cout << endl;
//	}
//	for (int i = parent_indexs.size() - 1; i>= 0; i--)
//	{
//		str_par_adress = PathToString(par_adresses[i]);
//		cout << '\t' << string(par_depth[i], '\t') << "</"
//			<< str_par_adress << '>' << endl;
//	}
//	cout << "</" << ent_str << '>' << endl;
//}

void Input_to_Xml_File(const string& ent_str, int counter, int previous_depth, int local_parent_depth, int parent_counter)
{
	string pth = "FirstFile.xml";
	ofstream fileout;
	fileout.open(pth);

	if (fileout.is_open() == false)
	{
		cout << "error" << endl;
	}
	else
	{
		vector<int> parent_indexs;
		vector<filesystem::path> par_adresses;
		vector<int> par_depth;

		vector<string> par_adresses1;

		parent_indexs.resize(0);
		par_depth.resize(0);

		filesystem::path parent_adress;
		filesystem::path prev_adress;

		fileout << "<xml version = '1.0' encoding = windows-1251" << '>' << endl;
		fileout << '<' << ent_str << '>' << endl;

		string str_par_adress;
		for (auto i = filesystem::recursive_directory_iterator(ent_str); i != filesystem::recursive_directory_iterator(); ++i)
		{
			string str_path = PathToString(*i);
			str_path = converter(str_path); //если хотим выводить только концевые названия
			for (int k = 0; (k < parent_indexs.size() - 1) && i.depth() < previous_depth; k++)
			{
				str_par_adress = PathToString(par_adresses[parent_indexs.size() - 1]);
				fileout << '\t' << string(local_parent_depth, '\t') << "</"
					<< str_par_adress << '>' << endl;
				if (parent_indexs.size() > 0)
				{
					parent_indexs.pop_back();
					par_adresses.pop_back();
					par_depth.pop_back();
				}
				parent_counter--;
				local_parent_depth--;
			}

			fileout << '\t' << string(i.depth(), '\t') << '<' << str_path << '>';

			if (i.depth() > previous_depth)
			{
				local_parent_depth = previous_depth;
				parent_counter = counter - 1;
				parent_indexs.push_back(parent_counter);
				parent_adress = prev_adress;
				par_adresses.push_back(parent_adress);

				par_depth.push_back(previous_depth);
			}

			previous_depth = i.depth();
			prev_adress = str_path;
			fileout << endl;
			counter++;
		}
		for (int i = parent_indexs.size() - 1; i >= 0; i--)
		{
			str_par_adress = PathToString(par_adresses[i]);
			fileout << '\t' << string(par_depth[i], '\t') << "</"
				<< str_par_adress << '>' << endl;
		}
		fileout << "</" << ent_str << '>' << endl;
	}
}


int main()
{
	string ent_str;
	cout << "Enter path in format dics:\\Folder1\\Folder2..." << endl; //"c:\\Program Files (x86)"
	cin >> ent_str;
	cout << "-----------------------------------------------------------------------------------" << endl;
	int counter(0), previous_depth(0), parent_depth(0), parent_counter(0);
	//XMLtoConsole(ent_str, counter, previous_depth, parent_depth, parent_counter);
	Input_to_Xml_File(ent_str, counter, previous_depth, parent_depth, parent_counter);

	return 0;}
