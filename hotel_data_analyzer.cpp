#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <cmath>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h> 
#endif
#include <filesystem>   

 using namespace std;

 namespace fs = std::filesystem;

 struct hotel
{
      int num;// 房号
      string variety;//种类
      int n_num1;  //all of n_num{1,2,3,...}are useless
      string name;//名字
      char state;//状态
      string ept;//空字符
      string opt;//有可能会有的编码
      int n_num2;
      int n_num3;
      string time;//次数，一般是0
      int quantity;//人数
      string c_time;//入住时间
      string l_time;//离开时间
      string code;//房价码
      double price;//房价
      string price2;//包价
      double own;//余额
      double credit;//信用，一般是0.00
      string kind;//团体，用于区分直连私联；
      string remark;//备注
      string n_num4;//手机号
      string account;//账号


   };
   
 tm get_current_date_tm() 
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    tm result = *local;
    result.tm_hour = 0;
    result.tm_min = 0;
    result.tm_sec = 0;
    return result;
}
string get_current_time_str() {
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    stringstream ss;
    ss << put_time(local, "%Y%m%d_%H%M%S");
    return ss.str();
}

   // 安全转换函数 有转化错误格式就变成0.0/0；
 int safe_stoi(const string& s) {
    string t = s;
    // 去除首尾空格
    t.erase(0, t.find_first_not_of(" \t\n\r"));
    t.erase(t.find_last_not_of(" \t\n\r") + 1);
    if (t.empty() || t == "-") return 0;
    try { return stoi(t); }
    catch (...) { return 0; }
}

 double safe_stod(const string& s) {
    string t = s;
    t.erase(0, t.find_first_not_of(" \t\n\r"));
    t.erase(t.find_last_not_of(" \t\n\r") + 1);
    if (t.empty() || t == "-") return 0.0;
    try { return stod(t); }
    catch (...) { return 0.0; }
}

 int days_since_checkin(const string& checkin_date, const string& checking_date) 
{

   int day,month,year,hour,minute,second;
   sscanf(checkin_date.c_str(), "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
   struct tm checkin_tm = {};
   checkin_tm.tm_year = year +2000- 1900; // tm_year is years since 1900
   checkin_tm.tm_mon = month - 1;    // tm_mon is 0-based
   checkin_tm.tm_mday = day;
   checkin_tm.tm_hour = 0;
   checkin_tm.tm_min = 0;
   checkin_tm.tm_sec = 0;
   time_t start_seconds = mktime(&checkin_tm);
   int matched=0;
   struct tm checking_tm = {};
   int year_o=year,month_o=month,day_o=day,hour_o=hour,minute_o=minute,second_o=second;
   matched=sscanf(checking_date.c_str(), "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
   if(matched==6)
   {
      if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(), "%d/%d/%d", &year, &month, &day);
   if(matched==3)
   {
      if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(), "%d-%d-%d", &year, &month, &day);
   if(matched==3)
   {
      if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(), "%d.%d.%d", &year, &month, &day);
   if(matched==3)
   {
      if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(), "%d.%d", &month, &day);
   if(matched==2)
   {
      year=year_o;
      if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(), "%d/%d", &month, &day);
   if(matched==2)
   {
     
      year=year_o;
       if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(),"%d-%d",&month,&day);
   if(matched==2)
   { 
      year=year_o;
       if(year<1000)
      {
         year+=2000;
      }   
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   matched=sscanf(checking_date.c_str(), "%d",  &day);
   if(matched==1)
   {
     year=year_o; month=month_o;
       if(year<1000)
      {
         year+=2000;
      }
      checking_tm.tm_year = year - 1900; // tm_year is years since 1900
      checking_tm.tm_mon = month - 1;    // tm_mon is 0-based
      checking_tm.tm_mday = day;
      time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
   }
   checking_tm = get_current_date_tm();
   time_t end_seconds = mktime(&checking_tm);
   long long seconds_diff = difftime(end_seconds, start_seconds);
   int days_diff = seconds_diff / (60 * 60 * 24);
   return days_diff;
}
double target_repar = 0.0;

vector<double> get_real_price(const string& remark)
{
   //xcout<<remark<<endl;
    vector<double> day_price;
    size_t pos = 0;

    while (pos < remark.size())
    {
        // 找下一个 '¥' 或 '￥'
        size_t pos_a = remark.find("￥", pos);
        size_t pos_h = remark.find("¥", pos);
        size_t found = string::npos;

        if (pos_a != string::npos && (pos_h == string::npos || pos_a < pos_h))
            found = pos_a;
        else if (pos_h != string::npos)
            found = pos_h;
        else
            break;  // 没有更多价格了
      cout<<found;
        // 提取数字部分
        size_t start = found + 1;
      while (start < remark.size() && !isdigit(remark[start]) && remark[start] != '.') {
         start++;
      }
      if (start >= remark.size()) {
         pos = found + 1;
         continue; // 跳过这个 ¥
      }
      size_t end = start;
      while (end < remark.size() && (isdigit(remark[end]) || remark[end] == '.')) {
         end++;
      }

        // 检查是否有 *n 重复标记
        int repeat = 1;
        if (end < remark.size() && remark[end] == '*')
        {
            size_t num_start = end + 1;
            size_t num_end = num_start;
            while (num_end < remark.size() && isdigit(remark[num_end]))
                num_end++;
            if (num_end > num_start)
            {
                string count_str = remark.substr(num_start, num_end - num_start);
                repeat = safe_stoi(count_str);
                if (repeat <= 0) repeat = 1;
            }
            end = num_end;  // 把 end 移到数字末尾，跳过 *n
        }

        //  提取价格并存入向量
        if (start < end)
        {
            string price_str = remark.substr(start, end - start);
            double price_val = safe_stod(price_str);
            for (int i = 0; i < repeat; i++)
                day_price.push_back(price_val);
        }
        // 移动 pos 到已处理的位置之后
        pos = end + 1;
        if (pos <= found) 
        {
          pos = found + 1;
        }  
    }
    
      cout<<day_price.size()<<"个";
    return day_price;
}
string checking_date;
string target_repar_str;
string room_num_str;
string file_name;
 int main(int argc,char* argv[])
 {
   #if defined(_WIN32) || defined(_WIN64)
   SetConsoleOutputCP(CP_UTF8);
   #endif
   // ---- 调试代码开始 ----
    cout << "=== 调试信息 ===" << endl;
    cout << "当前工作目录: " << fs::current_path() << endl;
    cout << "该目录下的所有文件:" << endl;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        cout << "  - [" << entry.path().filename().string() << "]" << endl;
    }
    cout << "=================" << endl;
    // ---- 调试代码结束 ----

    //拖动检查模块
    int states_in=0;//0=默认，1=拖动
    string return_name;
    if(argc>1)
    {
      for(int i=1;i<argc;i++)
      {
         string arg=argv[i];
         if(arg.find(".csv") != std::string::npos)
         {
            states_in=1;
            return_name=arg;
            break;
         }
      }
    }
   if(states_in==0) file_name = "hotelguests_in.csv";
   else
   {
      file_name=return_name;
   }


   cout<<"请输入想查询的日期！(默认今日)"<<endl;
   cout<<"请输入>>";
   getline(cin,checking_date);
   cout<<checking_date<<endl;
   cout<<"请输入目标repar!"<<endl;
   cout<<"请输入>>";//可修改成缓存模式，
   getline(cin,target_repar_str);
   cout<<endl;
   cout<<"请确认/输入房间总量!"<<endl;
   cout<<"请确认--数量为:115(若数字一致可不填并回车,若不同请输入)"<<endl<<"请输入>>";
   getline(cin, room_num_str);
   cout<<endl;


   double target_repar=safe_stod(target_repar_str);
   int room_num=115;
   if(safe_stoi(room_num_str)!=0)
   {
      room_num=safe_stoi(room_num_str);
   }


//   if(argc>1)
   ifstream file(file_name);
    // ... 你的后续代码
   if(!file.is_open())
   {
       cerr << "Error opening file!"<<file_name << endl;
      system("pause");
       return 1;
   }
   
   vector<hotel> h;
   vector<hotel> c;
   string line;
   string full_line;
   getline(file, line); // Skip the header line
   int l=0;
   while (getline(file, line))
   {
      //cout << "开始处理新行: [" << line << "]" << endl;
     if(full_line.empty())
     {
       full_line = line; // First line, no need to add a newline
     }
     else
     {
      int d_count = 0;
      for (int i=0;i<line.size();i++)
      {
          if(line[i]==',')
          {
              d_count++;
          }
      }
      if(d_count<18)
      {
               full_line += line;
               
      }
      if(d_count >=18)
      {
         cout<<full_line<<endl<<endl;
      stringstream ss(full_line);
      string num_i;// 房号
      string variety_i;//种类
      string n_num1_i;  //all of n_num{1,2,3,...}are useless
      string name_i;//名字
      string state_i;//状态
      string ept_i;//空字符
      string opt_i;//有可能会有的编码
      string n_num2_i;
      string n_num3_i;
      string time_i;//次数，一般是0
      string quantity_i;//人数
      string c_time_i;//入住时间
      string l_time_i;//离开时间
      string code_i;//房价码
      string price_i;//房价
      string price2_i;//包价
      string own_i;//余额
      string credit_i;//信用，一般是0.00
      string kind_i;//团体，用于区分直连私联；
      string remark_i;//备注
      string n_num4_i;//手机号
      string account_i;//账号
      // Read each field from the CSV line all of them are strings so define them all in string mode
      
      getline(ss, num_i, ',');
      getline(ss, variety_i, ',');
      getline(ss, n_num1_i, ',');
      getline(ss, name_i, ',');
      getline(ss, state_i, ',');
      getline(ss, ept_i, ',');
      getline(ss, opt_i, ',');
      getline(ss, n_num2_i, ',');
      getline(ss, n_num3_i, ',');
      getline(ss, time_i, ',');
      getline(ss, quantity_i, ',');
      getline(ss, c_time_i, ',');
      getline(ss, l_time_i, ',');
      getline(ss, code_i, ',');
      getline(ss, price_i, ',');
      getline(ss, price2_i, ',');
      getline(ss, own_i, ',');
      getline(ss, credit_i, ',');
      getline(ss, kind_i, ',');
      //getline(ss, remark_i, ','); 后三项单独查找
      //getline(ss, n_num4_i, ',');
      //getline(ss, account_i, ',');
      //separate the stringstream into dif virables

      string remaining;
      getline(ss, remaining);

      // 清理末尾的 \r 和 \n
      if (!remaining.empty() && (remaining.back() == '\r' || remaining.back() == '\n')) {
         remaining.pop_back();
      }

      // 处理空字符串情况
      if (remaining.empty()) {
         remark_i = "";
         n_num4_i = "";
         account_i = "";
      } else {
         size_t last_comma = remaining.rfind(',');
         if (last_comma == string::npos) {
            remark_i = remaining;
            n_num4_i = "";
            account_i = "";
         } else {
            account_i = remaining.substr(last_comma + 1);
            string temp = remaining.substr(0, last_comma);
            size_t second_last_comma = temp.rfind(',');
            if (second_last_comma == string::npos) {
                  remark_i = temp;
                  n_num4_i = account_i;
                  account_i = "";
            } else {
                  n_num4_i = temp.substr(second_last_comma + 1);
                  remark_i = temp.substr(0, second_last_comma);
            }
         }
      }
      
      int num=safe_stoi(num_i);
      string variety=variety_i;
      int n_num1=safe_stoi(n_num1_i);  
      string name=name_i;
      char state=state_i[0];
      string ept=ept_i;
      string opt=opt_i;
      int n_num2=safe_stoi(n_num2_i);
      int n_num3=safe_stoi(n_num3_i);
      string time=time_i;
      int quantity=safe_stoi(quantity_i);
      string c_time=c_time_i;
      string l_time=l_time_i;
      string code=code_i;
      double price=safe_stod(price_i);
      string price2=price2_i;
      double own=safe_stod(own_i);
      double credit=safe_stod(credit_i);
      string kind=kind_i;
      string remark=remark_i;
      string n_num4=n_num4_i;
      string account=account_i;
      hotel o={num,variety,n_num1,name,state,ept,opt,n_num2,n_num3,time,quantity,c_time,l_time,code,price,price2,own,credit,kind,remark,n_num4,account};
      
      h.push_back(o);
      //input finish
         full_line.clear();
         full_line=line; // Clear the full_line for the next record
      //cout << "成功读取一行数据: " << num << ", " << name << endl;
      }
      //cout<<"读取完成，共读取 "<<h.size()<<" 条记录."<<endl;
      //cin.ignore();
      //cin.get();
      //#if defined(_WIN32) || defined(_WIN64)
      //system("pause");
      //#endif
      }
   }   
   full_line+=line;
   stringstream ss(full_line);
      string num_i;// 房号
      string variety_i;//种类
      string n_num1_i;  //all of n_num{1,2,3,...}are useless
      string name_i;//名字
      string state_i;//状态
      string ept_i;//空字符
      string opt_i;//有可能会有的编码
      string n_num2_i;
      string n_num3_i;
      string time_i;//次数，一般是0
      string quantity_i;//人数
      string c_time_i;//入住时间
      string l_time_i;//离开时间
      string code_i;//房价码
      string price_i;//房价
      string price2_i;//包价
      string own_i;//余额
      string credit_i;//信用，一般是0.00
      string kind_i;//团体，用于区分直连私联；
      string remark_i;//备注
      string n_num4_i;//手机号
      string account_i;//账号
      // Read each field from the CSV line all of them are strings so define them all in string mode
      
      getline(ss, num_i, ',');
      getline(ss, variety_i, ',');
      getline(ss, n_num1_i, ',');
      getline(ss, name_i, ',');
      getline(ss, state_i, ',');
      getline(ss, ept_i, ',');
      getline(ss, opt_i, ',');
      getline(ss, n_num2_i, ',');
      getline(ss, n_num3_i, ',');
      getline(ss, time_i, ',');
      getline(ss, quantity_i, ',');
      getline(ss, c_time_i, ',');
      getline(ss, l_time_i, ',');
      getline(ss, code_i, ',');
      getline(ss, price_i, ',');
      getline(ss, price2_i, ',');
      getline(ss, own_i, ',');
      getline(ss, credit_i, ',');
      getline(ss, kind_i, ',');
      //getline(ss, remark_i, ','); 后三项单独查找
      //getline(ss, n_num4_i, ',');
      //getline(ss, account_i, ',');
      //separate the stringstream into dif virables

      string remaining;
      getline(ss, remaining);

      // 清理末尾的 \r 和 \n
      if (!remaining.empty() && (remaining.back() == '\r' || remaining.back() == '\n')) {
         remaining.pop_back();
      }

      // 处理空字符串情况
      if (remaining.empty()) {
         remark_i = "";
         n_num4_i = "";
         account_i = "";
      } else {
         size_t last_comma = remaining.rfind(',');
         if (last_comma == string::npos) {
            remark_i = remaining;
            n_num4_i = "";
            account_i = "";
         } else {
            account_i = remaining.substr(last_comma + 1);
            string temp = remaining.substr(0, last_comma);
            size_t second_last_comma = temp.rfind(',');
            if (second_last_comma == string::npos) {
                  remark_i = temp;
                  n_num4_i = account_i;
                  account_i = "";
            } else {
                  n_num4_i = temp.substr(second_last_comma + 1);
                  remark_i = temp.substr(0, second_last_comma);
            }
         }
      }
      
      int num=safe_stoi(num_i);
      string variety=variety_i;
      int n_num1=safe_stoi(n_num1_i);  
      string name=name_i;
      char state=state_i[0];
      string ept=ept_i;
      string opt=opt_i;
      int n_num2=safe_stoi(n_num2_i);
      int n_num3=safe_stoi(n_num3_i);
      string time=time_i;
      int quantity=safe_stoi(quantity_i);
      string c_time=c_time_i;
      string l_time=l_time_i;
      string code=code_i;
      double price=safe_stod(price_i);
      string price2=price2_i;
      double own=safe_stod(own_i);
      double credit=safe_stod(credit_i);
      string kind=kind_i;
      string remark=remark_i;
      string n_num4=n_num4_i;
      string account=account_i;
      hotel o={num,variety,n_num1,name,state,ept,opt,n_num2,n_num3,time,quantity,c_time,l_time,code,price,price2,own,credit,kind,remark,n_num4,account};
      
      h.push_back(o);
      //input finish
   file.close();
   //读取数据完成；
   //h是所有数据，c是私联的数据
   for(const auto& record : h) 
   {
      if(record.kind=="//Company_name")
      {
         c.push_back(record);
         
      }
   }
   double mach_count=0.0;//总房价
   double mach_count_p=0.0;//私联机器表码房价
   double human_count_p=0.0;//私联人工表码房价
   double l_price=0.0;//local price for the checking date   手工记录房价（查看日期）
   double count=0.0;
   int day=0;

   for(const auto& record : h) //总房价加和
   {
      day=days_since_checkin(record.c_time,checking_date);
      if(day<days_since_checkin(record.c_time,record.l_time)) mach_count+=record.price;

      
   }
   for(const auto& record : c) //私联房价加和
   {
      day=days_since_checkin(record.c_time,checking_date);
      if(day<days_since_checkin(record.c_time,record.l_time))
      {
         mach_count_p+=record.price;
         vector<double> day_price;//每天不同房价
         day_price=get_real_price(record.remark);
         day=days_since_checkin(record.c_time,checking_date);
         if(day_price.empty() )
         {
            human_count_p+=record.price;
         }//没有人工表码就用机器表码
         else if(day>=day_price.size())
         {
            human_count_p+=0;
            cout<<"+0"<<endl;
         }
         else if(day<day_price.size())
         {
            l_price=day_price[day];
            human_count_p+=l_price;
            cout<<"成功相加"<<human_count_p<<endl;
         }
      }
   }

   count = mach_count+human_count_p-mach_count_p;
      vector<int> room;
      for (const auto& record : h)
       {
         day=days_since_checkin(record.c_time,checking_date);
         if(day<days_since_checkin(record.c_time,record.l_time))
         {
         bool exists = false;
         for (size_t i = 0; i < room.size(); ++i) 
         {
            if (room[i] == record.num) 
            {
                  exists = true;
                  break;
            }
         }
         if (!exists) room.push_back(record.num);
      }
      }
   cout<<h.size()<<" "<<room.size();
   int room_left=room_num-room.size();
   double money=0.0;
   money=target_repar*room_num-count;
   double result=ceil(money/room_left);
   cout<<room_num<<endl;
   cout<<"改为"<<result<<"均价";
   cout<<endl<<file_name;
  string result_filename = "result_" + get_current_time_str() + ".txt";
   ofstream outfile(result_filename);
   if (outfile.is_open()) {
      cout << "结果已保存至: " << result_filename << endl;
   } else {
      cerr << "警告：无法创建输出文件！" << endl;
   }

   // 同时写入 cout 和 outfile
   cout << "总房价为：" << mach_count << endl;
   outfile << "总房价为：" << mach_count << endl;

   cout << "私联原房价为：" << mach_count_p << endl;
   outfile << "私联原房价为：" << mach_count_p << endl;

   cout << "数据捕捉修正后营业额为" << human_count_p << endl;
   outfile << "数据捕捉修正后营业额为" << human_count_p << endl;

   // 其他你想保存的信息（房间数、涨价值等）
   cout << "剩余房间数：" << room_left << endl;
   outfile << "剩余房间数：" << room_left << endl;

   cout << "建议调价：" << result << " 元/间" << endl;
   outfile << "建议调价：" << result << " 元/间" << endl;



return 0;
}
