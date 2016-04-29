#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <string>

using namespace std;


class User
{
	public:
		int ID;
		string name;
		double data[4];
		
		User(int ID, string name, double likeNewsPaper, double likeBook, double likeTV, double likeGame) : ID(ID), name(name)
		{
			data[0] = likeNewsPaper;
			data[1] = likeBook;
			data[2] = likeTV;
			data[3] = likeGame;
		}

		double angleBetween(User * whom)
		{
			int size = sizeof(data)/sizeof(data[0]);
			double dotProduct;
			double v1;
			double v2;
			for(int i=0; i<size; i++)
			{
				dotProduct += (this->data[i] * whom->data[i]);
				v1 += pow(this->data[i], 2);
				v2 += pow(whom->data[i], 2);
			}

			double crossProduct = sqrt(v1) * sqrt(v2);
			double cosine = dotProduct / crossProduct;
			return cosine;
		}
};

class Item
{
	public:
		int ID;
		string name;
		Item(int ID, string name) : ID(ID), name(name) { }
};

class Database
{
	public:
		string name;
		map <int, User *> users;
		map <string, Item *> items;
};



void initUserList(Database * db)
{
	User * A = new User(1, "A", 1, -1, 1, 1);
	User * B = new User(2, "B", 0, 1, -1, -1);
	User * C = new User(3, "C", 1, 1, -1, 0);
	User * D = new User(4, "D", -1, 0, 1, 0);
	User * E = new User(5, "E", 1, 1, 0, -1);
	User * F = new User(6, "F", 1, -1, 1, 0);

	db->users[0] = A;
	db->users[1] = B;
	db->users[2] = C;
	db->users[3] = D;
	db->users[4] = E;
	db->users[5] = F;
}

void initItemList(Database * db)
{
	Item * AA = new Item(1, "NewsPaper");
	Item * BB = new Item(2, "Book");
	Item * CC = new Item(3, "TV");
	Item * DD = new Item(4, "Game");

	db->items["NewsPaper"] = AA;
	db->items["Book"] = BB;
	db->items["TV"] = CC;
	db->items["Game"] = DD;
}

void initDatabase(Database * db)
{
	db->name = "ele";
}



User * findMostSimilarUser(User * who, map<int, User *> data)
{
	double max = -1;
	User * miror;
	for(map <int, User *>::iterator it = data.begin(); it != data.end(); it++)
	{
		if(who->name == it->second->name)
			continue;
		double similarity = who->angleBetween(it->second);
		cout << "similarity: " << similarity << endl;
		if(similarity > max)
		{
			max = similarity;
			miror = it->second;
		}
	}

	return miror;
}

User * getUser(Database * db, int UserID)
{
	return db->users[UserID];
}

Item * getItem(Database * db, string name)
{
	return db->items[name];
}

int getPreferFromUserWith(User * user, Item * item)
{
	return user->data[item->ID];
}

int main()
{

	Database * database = new Database;
	initDatabase(database);
	initUserList(database);
	initItemList(database);
	

	int userID = 3;	//D
	string itemName = "TV";
	

	User * currentUser = getUser(database, userID);
	Item * item = getItem(database, itemName);

	User * miror = findMostSimilarUser(currentUser, database->users);
	int likeness = getPreferFromUserWith(miror, item);

	cout << currentUser->name << " and " << miror->name << endl;
	cout << currentUser->name << "'s likeness to " << item->name << " is: " << likeness << "!" << endl;
	cout << "accuracy : " << currentUser->angleBetween(miror) << endl;
}