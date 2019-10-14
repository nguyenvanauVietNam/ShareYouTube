#pragma once
#define max_length 20
typedef struct Diem {
	int x;
	int y;
}Diem;
 typedef struct Dinh {
	int Chi_so;
	Diem toaDoDinh;
	Diem vungTiemCan[30][30];
}Dinh;
int diem_so_dinh = 0;
Dinh dsDinh[max_length];
//danh sách các đỉnh kề :: Ma trân kề

int MaTranKe[max_length][max_length];
//điếm số lượng Hamilton
int diem_Hamilton = 0;
//thiết kế cho việc tìm miền liên thông
int B[max_length];//
int C[max_length];
//chuỗi ghi Hamilton
typedef struct ChuoiHamilton {
	int sothutu;
	int hamtilton[20];
}ChuoiHamilton;
ChuoiHamilton dsHamilton[20];
//in ra chu trinh hamilton
System::String ^ Result()
{
	int cout = diem_so_dinh;
	System::String ^ string = "";
	string = string + B[cout];
	for (int i = cout-1;i >=1;i--)
	{
		string = string + "->" + B[i];
		dsHamilton[diem_Hamilton].sothutu = diem_Hamilton;
		dsHamilton[diem_Hamilton].hamtilton[i] = B[i];
	}
	string = string + "->"+ B[cout];
	diem_Hamilton++;
	
	return string ;
}


//khởi tạo mảng rổng
void ket_thuc_nhap_Canh()
{
	for (int i = 0;i <= max_length;i++)
	{
		C[i] = 0;
		B[i] = 0;
		for (int k = 1;k <= diem_so_dinh;k++)
		{
			for (int k1 = k+1;k1 <= diem_so_dinh;k1++)
			{
				if (MaTranKe[k][k1] == 1)
					MaTranKe[k1][k] = 1;
				else
					MaTranKe[k][k1] = 0;

			}
			MaTranKe[k][k] = 0;
		}
	}
}
/*
	Khởi tạo danh sách các đỉnh rỗng và vùng tiệm cận  = 0,0
*/


/*
	chỉ số đỉnh -> ánh xạ vào ma trận kề
	tọa độ x ,y -> lưu vào trong quá trình tạo cạnh
	tọa đo vùng tiệm cận -> set 1 vùng bằng x +20 ,y+20 trong 1 chiều dài và chiều rộng 20 so với x,y
	Để lấy làm vùng tiệm cận ,dễ dang cho việt set lại giá trị đỉnh khi tạo cạnh
*/
void Set_Dinh(int x ,int y,int k)
{
	
	int i=0, j=0;
	dsDinh[k].toaDoDinh.x = x;
	dsDinh[k].toaDoDinh.y = y;
	dsDinh[k].Chi_so = k;
	for (i = 1;i < 20;i++)
	{
		for (j = 1;j < 20;j++)
		{
			dsDinh[k].vungTiemCan[i][j].x = x + j;//tọa độ x
			dsDinh[k].vungTiemCan[i][j].y = y + i;//tọa độ y
		//	a += "["+dsDinh[k].vungTiemCan[i][j].x + "][" + dsDinh[k].vungTiemCan[i][j].y+"]"+"<>";
		}
		//a += "\n\r";
	}
	//return a;
}

//template
/*
	Thuật toán tìm đỉnh
	Áp dụng các quy tắc vùng tiệm cận của (Vi tích phân a2)Toán cao cấp.
	- Tìm các đỉnh trong vùng tiệm cận ,nếu tọa độ nó bằng  với tọa độ chuột -> return tọa độ đỉnh của vùng
*/
Dinh  timDinh(int x,int y)
{
	Dinh tam;
	tam.toaDoDinh.x = 0;
	tam.toaDoDinh.y = 0;
	for (int z = 1;z <= diem_so_dinh;z++)
	{
		for (int i = 0;i <20;i++)
			for (int j = 0;j <20;j++)
			{
				
				if(  y== dsDinh[z].vungTiemCan[i][j].y)
				if (x == dsDinh[z].vungTiemCan[i][j].x)
				{
					Dinh d;
					d.Chi_so = z;
					d.toaDoDinh.x= dsDinh[z].toaDoDinh.x;
					d.toaDoDinh.y = dsDinh[z].toaDoDinh.y;
					return (Dinh)d;
				}
			}

	}

	return (Dinh) tam;
}



//thuật toán tìm miền liên thông
//dựa trên giải thuật BFS
//hiện miền liên thông
//
//mảng chưa xét
Dinh tam2, dinhtam;
//biến để sử dụng BFS


/*
	Duyệt đồ thị khi đã có chu trình Hamilton
	Hoặc đã in miền liên thông

*/
//khai báo thư viện để sử dụng bộ nhớ động

//********************************************************************************//
//chuẩn bị cho duyệt đồ thị
//duyệt mienLienThong
//trả về của các miền
int returnDFS[max_length], returnBFS[max_length], returnMienLienThong[max_length][max_length];
//khai báo để hiện miền liên thông
int MaTran[20][20], so_dinh = 0, chuaXetQ[max_length], QUEUE[max_length], solt = 0, ii = 0;
int MangChuaDFS[max_length];
void InitMienLienThong()
{
	for (int ii = 1;ii <= so_dinh;ii++)
		for (int j = 1;j <= so_dinh;j++)
		{
			MaTran[ii][j] = MaTranKe[ii][j];
			returnMienLienThong[ii][j] = 0;

		}
	for (int ii = 1;ii <= so_dinh;ii++)
		chuaXetQ[ii] = 1;

	solt = 0;
}
//chuẩn bị cho duyệt theo chiều sâu:
int MaTranChieuSau[max_length][max_length], so_dinhDFS, chuaXetDFS[max_length];
void InitDFS()
{
	for (int i = 1;i <= diem_so_dinh;i++)
		for (int j = 1;j <= diem_so_dinh;j++)
		{
			if (MaTranKe[i][j] == 1)
				MaTranChieuSau[i][j] = MaTranKe[i][j];
			else
				MaTranChieuSau[i][j] = 0;
		}
	for (int i = 1; i <= diem_so_dinh;i++)
		chuaXetDFS[i] = 1;
}
//Chuẩn bị cho duyệt theo chiều rộng
int MaTranChieuRong[max_length][max_length], so_dinhBFS, chuaXetBFS[max_length];
int HangDoi[max_length];
void InitBFS()
{
	for (int i = 1;i <= diem_so_dinh;i++)
		for (int j = 1;j <= diem_so_dinh;j++)
		{
			if (MaTranKe[i][j] == 1)
				MaTranChieuRong[i][j] = 1;
			else
				MaTranChieuRong[i][j] = 0;
		}
	for (int i = 1; i <= diem_so_dinh;i++)
		chuaXetBFS[i] = 1;
}
int MangChuaBFS[max_length];
//*******************************************************************************//
namespace Do_an_monhoc
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		//biến điều khiển tạo cạnh và đỉnh
		// trong quá trình tạo cạnh thì đỉnh =false và ngược lại
	private: bool taoDinh = false;
	private: bool taoCanh = false;
	private:bool click = false;
	private: Bitmap  ^ _bm;
	private:Graphics ^ _g;
	private: System::Drawing::Point ^ _p1, ^ _p2, ^tam;
	private: System::Windows::Forms::Button^  btn_taoCanh;
	private: System::Windows::Forms::SaveFileDialog^  saveDothi;
	private: System::Windows::Forms::Button^  bntHamilton;

	private: System::Windows::Forms::Button^  bntLuuDoThi;
	private: System::Windows::Forms::Button^  btnOpen;
	private: System::Windows::Forms::Button^  bntExit;
	private:System::String ^str;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	
	private: System::Windows::Forms::Button^  DFSbtn;
			 //Biến để xem đồ thị có hamilton hay không? cho phép tạo miền liên thông
	private: bool kiemtraHamilton = false, hienmienlienthong = false;


	private: System::Windows::Forms::Button^  btnRefesh;
	private: System::Windows::Forms::Button^  bntHuongDan;


	private: System::Windows::Forms::OpenFileDialog^  OpenDothi;



	public:
		MyForm(void)
		{
			InitializeComponent();
			_bm = gcnew System::Drawing::Bitmap(this->Width, this->Height);
			_g = System::Drawing::Graphics::FromImage(_bm);


			//giảm hiện tượng giật giật
			//với biến này thì control sẽ nhận chỉ thị trực tiếp không phu thuộc vào hệ điều hành
			this->SetStyle(ControlStyles::UserPaint, true);
			//bổ trợ cho user Panit ,ngắt mọi tin nhắn từ win down và cập nhật paint nhanh hơn

			this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
			this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);


			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btn_taoDinh;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btn_taoDinh = (gcnew System::Windows::Forms::Button());
			this->btn_taoCanh = (gcnew System::Windows::Forms::Button());
			this->saveDothi = (gcnew System::Windows::Forms::SaveFileDialog());
			this->OpenDothi = (gcnew System::Windows::Forms::OpenFileDialog());
			this->bntHamilton = (gcnew System::Windows::Forms::Button());
			this->bntLuuDoThi = (gcnew System::Windows::Forms::Button());
			this->btnOpen = (gcnew System::Windows::Forms::Button());
			this->bntExit = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->DFSbtn = (gcnew System::Windows::Forms::Button());
			this->btnRefesh = (gcnew System::Windows::Forms::Button());
			this->bntHuongDan = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btn_taoDinh
			// 
			this->btn_taoDinh->BackColor = System::Drawing::SystemColors::Control;
			this->btn_taoDinh->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_taoDinh->ForeColor = System::Drawing::Color::Black;
			this->btn_taoDinh->Location = System::Drawing::Point(14, 14);
			this->btn_taoDinh->Name = L"btn_taoDinh";
			this->btn_taoDinh->Size = System::Drawing::Size(115, 45);
			this->btn_taoDinh->TabIndex = 0;
			this->btn_taoDinh->Text = L"Tạo đỉnh";
			this->btn_taoDinh->UseVisualStyleBackColor = false;
			this->btn_taoDinh->Click += gcnew System::EventHandler(this, &MyForm::btn_taoDinh_Click);
			// 
			// btn_taoCanh
			// 
			this->btn_taoCanh->BackColor = System::Drawing::SystemColors::Control;
			this->btn_taoCanh->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(163)));
			this->btn_taoCanh->Location = System::Drawing::Point(12, 78);
			this->btn_taoCanh->Name = L"btn_taoCanh";
			this->btn_taoCanh->Size = System::Drawing::Size(115, 48);
			this->btn_taoCanh->TabIndex = 1;
			this->btn_taoCanh->Text = L"Tạo cạnh";
			this->btn_taoCanh->UseVisualStyleBackColor = false;
			this->btn_taoCanh->Click += gcnew System::EventHandler(this, &MyForm::btn_taoCanh_Click);
			// 
			// saveDothi
			// 
			this->saveDothi->FilterIndex = 2;
			this->saveDothi->InitialDirectory = L"E:\\visual";
			this->saveDothi->Title = L"Lưu đồ thị";
			this->saveDothi->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveDothi_FileOk);
			// 
			// OpenDothi
			// 
			this->OpenDothi->FilterIndex = 2;
			this->OpenDothi->InitialDirectory = L"E:\\visual";
			this->OpenDothi->Title = L"Mở đồ thị";
			// 
			// bntHamilton
			// 
			this->bntHamilton->BackColor = System::Drawing::SystemColors::Control;
			this->bntHamilton->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bntHamilton->ForeColor = System::Drawing::Color::Black;
			this->bntHamilton->Location = System::Drawing::Point(14, 150);
			this->bntHamilton->Name = L"bntHamilton";
			this->bntHamilton->Size = System::Drawing::Size(113, 43);
			this->bntHamilton->TabIndex = 2;
			this->bntHamilton->Text = L"Hamilton";
			this->bntHamilton->UseVisualStyleBackColor = false;
			this->bntHamilton->Click += gcnew System::EventHandler(this, &MyForm::bntHamilton_Click);
			// 
			// bntLuuDoThi
			// 
			this->bntLuuDoThi->Location = System::Drawing::Point(76, 362);
			this->bntLuuDoThi->Name = L"bntLuuDoThi";
			this->bntLuuDoThi->Size = System::Drawing::Size(57, 38);
			this->bntLuuDoThi->TabIndex = 4;
			this->bntLuuDoThi->Text = L"Lưu";
			this->bntLuuDoThi->UseVisualStyleBackColor = true;
			this->bntLuuDoThi->Click += gcnew System::EventHandler(this, &MyForm::bntLuuDoThi_Click);
			// 
			// btnOpen
			// 
			this->btnOpen->Location = System::Drawing::Point(14, 364);
			this->btnOpen->Name = L"btnOpen";
			this->btnOpen->Size = System::Drawing::Size(56, 36);
			this->btnOpen->TabIndex = 5;
			this->btnOpen->Text = L"Mở";
			this->btnOpen->UseVisualStyleBackColor = true;
			this->btnOpen->Click += gcnew System::EventHandler(this, &MyForm::btnOpen_Click);
			// 
			// bntExit
			// 
			this->bntExit->Location = System::Drawing::Point(12, 406);
			this->bntExit->Name = L"bntExit";
			this->bntExit->Size = System::Drawing::Size(115, 38);
			this->bntExit->TabIndex = 6;
			this->bntExit->Text = L"Thoát";
			this->bntExit->UseVisualStyleBackColor = true;
			this->bntExit->Click += gcnew System::EventHandler(this, &MyForm::bntExit_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(135, 310);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 15);
			this->label1->TabIndex = 7;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->bntHuongDan);
			this->groupBox1->Controls->Add(this->DFSbtn);
			this->groupBox1->Location = System::Drawing::Point(14, 212);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(115, 113);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Miền liên thông";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// DFSbtn
			// 
			this->DFSbtn->Location = System::Drawing::Point(6, 21);
			this->DFSbtn->Name = L"DFSbtn";
			this->DFSbtn->Size = System::Drawing::Size(103, 43);
			this->DFSbtn->TabIndex = 10;
			this->DFSbtn->Text = L"Hiện miền Liên Thông";
			this->DFSbtn->UseVisualStyleBackColor = true;
			this->DFSbtn->Click += gcnew System::EventHandler(this, &MyForm::DFSbtn_Click);
			// 
			// btnRefesh
			// 
			this->btnRefesh->Location = System::Drawing::Point(29, 331);
			this->btnRefesh->Name = L"btnRefesh";
			this->btnRefesh->Size = System::Drawing::Size(75, 23);
			this->btnRefesh->TabIndex = 9;
			this->btnRefesh->Text = L"Làm tươi";
			this->btnRefesh->UseVisualStyleBackColor = true;
			this->btnRefesh->Click += gcnew System::EventHandler(this, &MyForm::btnRefesh_Click);
			// 
			// bntHuongDan
			// 
			this->bntHuongDan->Location = System::Drawing::Point(6, 70);
			this->bntHuongDan->Name = L"bntHuongDan";
			this->bntHuongDan->Size = System::Drawing::Size(103, 37);
			this->bntHuongDan->TabIndex = 10;
			this->bntHuongDan->Text = L"Hướng dẫn";
			this->bntHuongDan->UseVisualStyleBackColor = true;
			this->bntHuongDan->Click += gcnew System::EventHandler(this, &MyForm::bntHuongDan_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(834, 456);
			this->Controls->Add(this->btnRefesh);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->bntExit);
			this->Controls->Add(this->btnOpen);
			this->Controls->Add(this->bntLuuDoThi);
			this->Controls->Add(this->bntHamilton);
			this->Controls->Add(this->btn_taoCanh);
			this->Controls->Add(this->btn_taoDinh);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Đồ án Hamilton";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::My_Panit);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Down);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::mouse_movie);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::Mouse_Up);
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Mouse_Down(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (taoCanh == true)
			if (e->X >= 150 && e->X <= 800 && e->Y <= 300)
			{
				
				tam2.toaDoDinh.x = e->X;
				tam2.toaDoDinh.y = e->Y;
				tam2.Chi_so = diem_so_dinh;
				if (timDinh(e->X,e->Y).toaDoDinh.x == 0)
				{

					System::Windows::Forms::MessageBox::Show(this, L"Bạn nên bắt đầu từ một dỉnh và kết thúc với 1 đỉnh khác", L"Thông báo", MessageBoxButtons::OK, MessageBoxIcon::Stop);
				}
				else
				{
					click = true;

					_p1 = gcnew Point(timDinh(e->X,e->Y).toaDoDinh.x, timDinh(e->X,e->Y).toaDoDinh.y);

				}
			}

		//template để kiểm thử dsDinh




	

		if (taoDinh == true)
			if (e->X >= 150 && e->X <= 800 && e->Y <= 300)
			{
				if (diem_so_dinh > 19) {
					taoDinh = false;
					MessageBox::Show(this, L"Cảnh báo", L"Bạn tạo vượt quá số đỉnh ", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				diem_so_dinh = diem_so_dinh + 1;
				int x = e->X;
				int y = e->Y;
				
				Set_Dinh(x, y, diem_so_dinh);
				String ^myString = Convert::ToString(diem_so_dinh);
				System::Drawing::Font ^ myFont =
					gcnew System::Drawing::Font("Arial", 8);
				System::Drawing::SolidBrush^ myBrush =
					gcnew System::Drawing::SolidBrush(Color::Black);
				System::Drawing::StringFormat^ myFormat =
					gcnew System::Drawing::StringFormat();
				System::Drawing::SolidBrush ^b1 = gcnew System::Drawing::SolidBrush(Color::Purple);
				System::Drawing::Pen ^ myPen = gcnew System::Drawing::Pen(Color::Purple);
				_g->DrawEllipse(myPen, e->X, e->Y, 20, 20);
				_g->DrawString(myString, myFont, myBrush, (float)e->X + 3, (float)e->Y + 3, myFormat);
				this->BackgroundImage = (Bitmap ^)_bm->Clone();



				delete myString;
				delete b1;
				delete myFont;
				delete myBrush;
				delete myFormat;
				delete myPen;

			}
			else
			{
				MessageBox::Show(this, L"Cảnh báo", L"Bạn không thể tạo đỉnh tại đây!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
	}
	private: System::Void btn_taoDinh_Click(System::Object^  sender, System::EventArgs^  e) {
		taoDinh = true;
		taoCanh = false;
		daInHamilton = false;
	}

	private: System::Void Mouse_Up(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (taoCanh)
		{
			
			click = false;
			Pen ^p = gcnew Pen(Color::Red, 2);
			dinhtam.toaDoDinh.x = e->X;
			dinhtam.toaDoDinh.y = e->Y;
			if (timDinh(dinhtam.toaDoDinh.x, dinhtam.toaDoDinh.y).toaDoDinh.x != 0)
			{
				//gọi A B C D là các góc của hình vuông
				// A  = x-10,y  ,B = x,y-10, C x-10,y-10, d=x -20,y-10
				_p2 = gcnew Point(timDinh(e->X,e->Y).toaDoDinh.x, timDinh(e->X,e->Y).toaDoDinh.y);
				if (_p1->X != _p2->X && _p1->Y != _p2->Y)
				{
					if(_p1->X >_p2->X)
						
							_g->DrawLine(p, _p1->X, _p1->Y+10, _p2->X+20, _p2->Y+10);//lấy điêm 1D ,2A
					if(_p1->X <_p2->X)
						_g->DrawLine(p, _p1->X+20, _p1->Y+10 , _p2->X, _p2->Y+10);

					this->BackgroundImage = (Bitmap ^)_bm->Clone();
					//
					MaTranKe[timDinh(tam2.toaDoDinh.x, tam2.toaDoDinh.y).Chi_so][timDinh(dinhtam.toaDoDinh.x, dinhtam.toaDoDinh.y).Chi_so] = 1;
					MaTranKe[timDinh(dinhtam.toaDoDinh.x, dinhtam.toaDoDinh.y).Chi_so][timDinh(tam2.toaDoDinh.x, tam2.toaDoDinh.y).Chi_so] = 1;
					
					
				}
				else
				{
					this->Refresh();
				}
				
				delete _p2;
				delete _p1;
				delete p;
			}
			else
			{
				MessageBox::Show(this, L"Bạn nên kết thúc tại 1 đỉnh khác", L"Thông báo", MessageBoxButtons::OK, MessageBoxIcon::Error);
				//kiểm thử refresh trên form MyForm
				//System::Drawing::Pen^ tamp = gcnew System::Drawing::Pen(Color::White,2);
				//_g->DrawLine(tamp, _p1->X, _p1->Y, e->X, e->Y);
				this->Refresh();

				//delete tamp;
				delete tam;
			}
		}

	}
	private: System::Void btn_taoCanh_Click(System::Object^  sender, System::EventArgs^  e) {
		if (diem_so_dinh > 1)
		{
			daInHamilton = false;
			taoCanh = true;
			taoDinh = false;
			HienMienLienThong_BOOL = false;
			
			
		}
		else
		{


			MessageBox::Show(this, L"Bạn nên tạo đỉnh trước: ít nhất hai đỉnh để tạo đồ thị", L"Thông báo", MessageBoxButtons::OK, MessageBoxIcon::Warning);

		}
	}

	private: System::Void mouse_movie(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (click &&taoCanh)
		{
			tam = gcnew Point(e->X, e->Y);
			this->Refresh();



		}
	}
	private: System::Void My_Panit(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		if (click)
		{
			Pen ^p = gcnew Pen(Color::Red);
			e->Graphics->DrawLine(p, _p1->X, _p1->Y, tam->X, tam->Y);
		}
	}

	private: System::Void saveDothi_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
	//tạo biến in ra hamilton
	
			 private: System::String ^hamilton ="";
					   private: bool DieuKhienIN = true;
			 //thoát chương trình
	private: System::Void bntExit_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::Exit();
	}
			 //Hamilton
			
	private:void Hamilton(int *B, int *C, int i) {
		
		int j;
		for (j = 1;j <= diem_so_dinh;j++)
		{
			if (MaTranKe[B[i - 1]][j] == 1 && C[j] == 0)
			{
				B[i] = j;
				C[j] = 1;
				if (i < diem_so_dinh)Hamilton(B, C, i + 1);
				else
					if (B[i] == B[0]) {

						
						
							str = Result();
							hamilton += L"Chu trình :" + str + "\n";
						
					}
				C[j] = 0;
			}
		}
	}
	private:bool daInHamilton = false;
	private: System::Void bntHamilton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (!daInHamilton) {
			ket_thuc_nhap_Canh();
			taoCanh = false;
			taoCanh = false;
			B[0] = 1;
			Hamilton(B, C, 1);
			if (diem_Hamilton == 0)
			{
				label1->Text = L"Không có Hamilton";
			}
			else
			{

				System::String ^ tieude = L"Chu trình Hamilton:" + "\n";
				label1->Text = tieude + hamilton;
				hamilton = L"";
				daInHamilton = true;
			}
			
		}
		
	}
	private: System::Void bntLuuDoThi_Click(System::Object^  sender, System::EventArgs^  e) {
		
		saveDothi->Filter = "Text Files (*.txt)|*.txt| Word 97-2003 (*.doc)|*.doc |Word Document(*.docx)|.docx|All files (*.*)|*.*   ";
		saveDothi->FilterIndex = 1;
		saveDothi->RestoreDirectory = true;
		String ^ path = saveDothi->FileName;
		if (saveDothi->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			System::IO::StreamWriter ^ myStream = gcnew System::IO::StreamWriter(saveDothi->OpenFile());
			myStream->WriteLine(Convert::ToString(diem_so_dinh));
			for (int line = 1,line2;line <= diem_so_dinh;line++) {
				for (line2 = 1;line2 < diem_so_dinh;line2++)
				{
					myStream->Write(Convert::ToString(MaTranKe[line][line2]));
					myStream->Write(" ");
				}
				myStream->Write(MaTranKe[line][diem_so_dinh]+"\r\n");
			}
		
			//ghi danh sách đỉnh (kèm theo tọa độ)
			//dòng thứ nhất tọa độ x ,dòng thứ 2 tọa độ y
			for (int line = 1;line <= diem_so_dinh;line++)
			{
				myStream->WriteLine(dsDinh[line].toaDoDinh.x);
				myStream->WriteLine(dsDinh[line].toaDoDinh.y);
			}
				myStream->Close();
				MessageBox::Show(this,L"Đã lưu thành công!", L"Thông báo", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		System::IO::StreamReader ^ myStream;
		taoDinh = false;
		taoCanh = false;
		daInHamilton = false;


		OpenDothi->Filter = "Text Files (*.txt)|*.txt|Word 97 -2003 (*.doc)|*.doc|Word Document (*.docx)|*.docx|All files (*.*)|*.*";
		OpenDothi->FilterIndex = 1;
		OpenDothi->RestoreDirectory = true;

		if (OpenDothi->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			//tạo đối tượng streamreader để đọc file
			myStream = gcnew StreamReader(OpenDothi->OpenFile());
			diem_so_dinh = Convert::ToInt32(myStream->ReadLine());
			
		  //cho ma trận kể thứ [line][line2] = các điểm
			String ^ a;
			int aa;
			
		for (int line = 1, line2 = 0,sin =0;line <= diem_so_dinh;line++)
			{

				for (line2 = 1,sin=1;line2 <=diem_so_dinh*2 +1,sin<=diem_so_dinh ;line2++)
				{

					aa = myStream->Read();

					if (aa == 32 || aa == 13 || aa == 10)
						continue;
					else if (aa == 48)
					{
						MaTranKe[line][sin] = 0;
						a += "><" + MaTranKe[line][sin];
						sin++;
					}
					else if (aa == 49)
					{
						MaTranKe[line][sin] = 1;
						a += "><" + MaTranKe[line][sin];
						sin++;
					}
					else
						continue;   // bắt ngoại lệ nếu vượt ra các ký tự
				}
				a += "\n\r";
			}      
			 myStream->ReadLine();
			//nhập ds Dinh
			for (int line = 1;line <= diem_so_dinh;line++)
			{
				String^ tampp,^tampp2;
					tampp = myStream->ReadLine();
				int x = Int32::Parse(tampp);
				tampp2  = myStream->ReadLine();
				int y= Int32::Parse(tampp2);
				Set_Dinh( x, y, line);
				a += L"tọa độ X:" +tampp+L"Tọa độ Y:"+tampp2+ "\n\r";
				delete tampp,tampp2;
			}
			 
			myStream->Close();
			// 
			//Load lại
			for (int line = 1;line <= diem_so_dinh;line++)
			{
				//vẻ đỉnh đồ thị
				String ^myString = Convert::ToString(dsDinh[line].Chi_so);
				System::Drawing::Font ^ myFont =
					gcnew System::Drawing::Font("Arial", 8);
				System::Drawing::SolidBrush^ myBrush =
					gcnew System::Drawing::SolidBrush(Color::Black);
				System::Drawing::StringFormat^ myFormat =
					gcnew System::Drawing::StringFormat();
				System::Drawing::SolidBrush ^b1 = gcnew System::Drawing::SolidBrush(Color::Purple);
				_g->FillEllipse(b1,dsDinh[line].toaDoDinh.x, dsDinh[line].toaDoDinh.y, 20, 20);
				_g->DrawString(myString, myFont, myBrush, (float)dsDinh[line].toaDoDinh.x + 3,(float)dsDinh[line].toaDoDinh.y + 3, myFormat);
				this->BackgroundImage = (Bitmap ^)_bm->Clone();



				delete myString;
				delete b1;
				delete myFont;
				
			}
			//vẻ lại cạnh đồ thị
			for(int i =1;i<=diem_so_dinh;i++)
				for (int j = i + 1;j <= diem_so_dinh;j++)
				{
					if (MaTranKe[i][j] == 1)
					{
						Pen ^p = gcnew Pen(Color::Red, 2);
						if (dsDinh[i].toaDoDinh.x > dsDinh[j].toaDoDinh.x)

							_g->DrawLine(p, dsDinh[i].toaDoDinh.x, dsDinh[i].toaDoDinh.y+10, dsDinh[j].toaDoDinh.x+20, dsDinh[j].toaDoDinh.y+10);
						if (dsDinh[i].toaDoDinh.x < dsDinh[j].toaDoDinh.x)
							_g->DrawLine(p, dsDinh[i].toaDoDinh.x+20, dsDinh[i].toaDoDinh.y+10, dsDinh[j].toaDoDinh.x, dsDinh[j].toaDoDinh.y+10);

						
						this->BackgroundImage = (Bitmap ^)_bm->Clone();
					}
				}
			label1->Text = L"Đã mở";
		}
	}
	//************************************************************************************//
			 // hien thi thành phần liên thông




private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btnRefesh_Click(System::Object^  sender, System::EventArgs^  e) {
	
	
	Application::Restart();
}
		 /*thuat toán miền liên thông dựa trên việc tìm kiếm theo chiều rộng 
		 hoặc kết luận dựa trên tính liên thông của đồ thị*/
private:String ^tieude = L"Đồ thị liên thông:\n";
private:String^ Result_MienLienThong(int *chuaXetQ, int so_dinh, int solt)
{
	String^ mienLienThong;
	if (solt == 1)
	{
		HienTheoChieuSau = true;
		HienBFS = true;
			return tieude ;

	}
	else
	{
		HienBFS = false;
		HienTheoChieuSau = false;
	}
	for (int ii = 1;ii <= solt;ii++)
	{
		mienLienThong += L"\nThành phần liên thông thứ " + ii + ":";
		for (int j = 1;j <= so_dinh;j++)
		{
			if (chuaXetQ[j] == ii)
			{
				System::Drawing::SolidBrush ^b1;
				if (ii == 1)b1 = gcnew SolidBrush(Color::Black);
				else if (ii == 2)b1 = gcnew SolidBrush(Color::Brown);
				else if (ii == 3)b1 = gcnew SolidBrush(Color::Yellow);
				else if (ii == 4) b1 = gcnew SolidBrush(Color::YellowGreen);
				else if (ii == 5)b1 = gcnew SolidBrush(Color::Pink);
				else if (ii == 6)b1 = gcnew SolidBrush(Color::Chocolate);
				/* tạo chữ lên hình tròn */
				System::Drawing::Font ^ myFont =
					gcnew System::Drawing::Font("Arial", 8);
				System::Drawing::SolidBrush^ myBrush =
					gcnew System::Drawing::SolidBrush(Color::White);
				System::Drawing::StringFormat^ myFormat =
					gcnew System::Drawing::StringFormat();
				String ^myString = Convert::ToString(j);

				_g->FillEllipse(b1, dsDinh[j].toaDoDinh.x, dsDinh[j].toaDoDinh.y, 20, 20);
				_g->DrawString(myString, myFont, myBrush, (float)dsDinh[j].toaDoDinh.x + 3, (float)dsDinh[j].toaDoDinh.y + 3, myFormat);

				this->BackgroundImage = (Bitmap ^)_bm->Clone();
				mienLienThong = mienLienThong + " " + j;
				returnMienLienThong[ii][j] = j;
				
				delete b1;
			}
		}
	}
	return mienLienThong;
}
private:void Mienlienthong(int MaTran[][max_length], int so_dinh, int ii, int *solt, int chuaXetQ[], int QUEUE[max_length])
{
	int u, dauQ, cuoiQ, j;
	dauQ = 1; cuoiQ = 1;
	QUEUE[cuoiQ] = ii;
	chuaXetQ[ii] = *solt;
	while (dauQ <= cuoiQ)
	{
		u = QUEUE[dauQ];  dauQ = dauQ + 1;
		for (j = 1; j <= so_dinh;j++)
		{
			if (MaTran[u][j] == 1 && chuaXetQ[j] == 0)
			{
				cuoiQ = cuoiQ + 1;
				QUEUE[cuoiQ] = j;
				chuaXetQ[j] = *solt;
			}
		}

	}

}

private:bool HienMienLienThong_BOOL= false;
private:String ^ HienmienLienThongSTR;
private: System::Void DFSbtn_Click(System::Object^  sender, System::EventArgs^  e) {
	HienMienLienThong_BOOL = true;
	if (HienMienLienThong_BOOL)
	{
		taoCanh = false;
		taoDinh = false;
		InitMienLienThong();
		so_dinh = diem_so_dinh;
		for (ii = 1; ii <= so_dinh;ii++)
		{
			if (chuaXetQ[ii] == 0)
			{
				solt = solt + 1;
				Mienlienthong(MaTranKe, so_dinh, ii, &solt, chuaXetQ, QUEUE);
			}
			HienmienLienThongSTR = Result_MienLienThong(chuaXetQ, so_dinh, solt);
		}
		if (HienTheoChieuSau && HienBFS)
		{
			so_dinhDFS = diem_so_dinh;
			InitDFS();
			for(int i = 1; i <= so_dinhDFS;i++)
				if (chuaXetDFS[i]==1)
					DuyetDoThiTheoChieuSau(MaTranChieuSau,so_dinhDFS, i, chuaXetDFS);
			so_dinhBFS = diem_so_dinh;
			InitBFS();
			for (int i = 1;i <= so_dinhBFS;i++)
				if (chuaXetBFS[i])
					DuyetTheoChieuRong(i);
			label1->Text = HienmienLienThongSTR + DFS +BFS;
			HienBFS = false;
			HienTheoChieuSau = false;
		}else
		label1->Text = HienmienLienThongSTR;
		so_dinh = 0;solt = 0;
	}
}
private:int KiemTraMangChuaDFS(int x)
		 {
			 for (int i = 1;i <= diem_so_dinh;i++)
			 {
				 if (MangChuaDFS[i] == x)
					 return x;

			 }
			 return 0;
		 }
private:String ^DFS=L"\nDFS:";
private:int KeyCS = 1;
		private:bool HienTheoChieuSau = false;
private:void DuyetDoThiTheoChieuSau(int MaTranChieuSau[][max_length],int so_dinhDFS,int v ,int chuaXetDFS[max_length])
{
	if (KiemTraMangChuaDFS(v) != v)
	{
		MangChuaDFS[KeyCS] = v;
		KeyCS++;
	}
	DFS += " " + v;
	int  u;
	chuaXetDFS[v] = 0;
	for (u = 1;u <= so_dinhDFS;u++)
		if (MaTranChieuSau[v][u] == 1 && chuaXetDFS[u] == 1)
			DuyetDoThiTheoChieuSau(MaTranChieuSau, so_dinhDFS, u, chuaXetDFS);
}
private:String ^BFS = L"\nBFS:";
private:bool HienBFS = false;
void DuyetTheoChieuRong(int x)
{
	int dauQ, cuoiQ, u;
	dauQ = 1;cuoiQ = 1;
	HangDoi[cuoiQ] = x;
	chuaXetBFS[x] = 0;
	while (dauQ <= cuoiQ)
	{
		u = HangDoi[dauQ];
		BFS += " " + u;
		dauQ=dauQ+1;
		for (int j = 1;j <=so_dinhBFS;j++)
		{
			if (MaTranChieuRong[u][j] == 1 && chuaXetBFS[j])
			{
				cuoiQ=cuoiQ+1;
				HangDoi[cuoiQ] = j;
				chuaXetBFS[j] = 0;
			}
		}
	}
}

private: System::Void bntHuongDan_Click(System::Object^  sender, System::EventArgs^  e) {
	String ^ HuongDan = L"- Nhấp vào [Tạo đỉnh] và click chuột trái lên cửa số, phần phía bên phải các nút\r\n."
		+ L"- Nhấp vào [tạo cạnh] để tạo cạnh cho đồ thị, nhấp vào 1 đỉnh sau đó giữ chuột và  di chuyển chuột tới đỉnh kia\r\n rồi thả ra."
		+ L"\r\n- Nhấp vào Hamilton để thực hiên tìm chu trình Hamtilton."
		+ L"\r\n- Lưu lại nhấp[Lưu] và mở trở lại[ Mở]."
		+ L"\r\n- Nhấn vào [làm tươi] nếu muốn thực hiện lại các chức năng nhưng với đồ thị khác."
		+ L"\r\n- Nhấn thoát để thoát chương trình.";
	MessageBox::Show(this, HuongDan, L"Hướng dẫn sử dụng", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
};
}
