using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Excel = Microsoft.Office.Interop.Excel;
using Word = Microsoft.Office.Interop.Word;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        class Human
        {
            public Human()
            {
                fstName = lstName = fathName = date = null;
            }
            public string fstName, lstName, fathName, date;
            public void Init(string fstNameCell, string lstNameCell, string fathNameCell, string dateCell)
            {
                fstName = fstNameCell;
                lstName = lstNameCell;
                fathName = fathNameCell;
                date = dateCell;
            }
            public bool Comparison(string fullName, string dateTwo)
            {
                string[] names = fullName.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                if (fstName == names[0])
                {
                    if (lstName == names[1])
                    {
                        if (fathName == names[2])
                        {
                            if (date == dateTwo)
                                return true;
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                else
                    return false;
            } 
            public void Write(Word.Application WordAppRes, int i)
            {                   
                WordAppRes.Documents[1].Tables[1].Rows.Add();
                WordAppRes.Documents[1].Tables[1].Cell(i, 1).Range.Text = i.ToString();
                WordAppRes.Documents[1].Tables[1].Cell(i, 2).Range.Text = fstName;
                WordAppRes.Documents[1].Tables[1].Cell(i, 3).Range.Text = lstName;
                WordAppRes.Documents[1].Tables[1].Cell(i, 4).Range.Text = fathName;
                WordAppRes.Documents[1].Tables[1].Cell(i, 5).Range.Text = date;
            }
        }

        private Excel.Application ExcelApp;
        private Word.Application WordApp;
        private Word.Application WordAppRes = new Word.Application();
        private Human hum = new Human();
        
        public Form1()
        {
            InitializeComponent();

            openFileDialog1.Filter = "Excel files(*.xlsx)|*.xlsx|All files(*.*)|*.*";
            openFileDialog2.Filter = "Text files(*.doc)|*.doc|Text(*.docx)|*.docx|All files(*.*)|*.*";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void CreateTableRes()
        {
            object start = 0, end = 0;
            Word.Document WordRes = WordAppRes.Documents.Add();
            Word.Range TableLocation = WordRes.Range(ref start, ref end);
            WordRes.Tables.Add(TableLocation, 1, 5);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            CreateTableRes();
            Excel.Worksheet ExcelName = OpenExcel();
            Word.Table WordName = OpenWord();
            ReadExel(hum, ExcelName, WordName);
            SaveRes();
            MessageBox.Show("Успех! Ищите файл на рабочем столе.");
            WordApp.Quit();
            WordAppRes.Quit();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (openFileDialog2.ShowDialog() == DialogResult.Cancel)
                return;
            string filename1 = openFileDialog2.FileName;
            textBox2.Text = filename1;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            string filename = openFileDialog1.FileName;
            textBox1.Text = filename;
        }
        private Excel.Worksheet OpenExcel()
        {
            ExcelApp = new Excel.Application();
            ExcelApp.Visible = true;
            Excel.Workbook ObjWorkBook = ExcelApp.Workbooks.Open(openFileDialog1.FileName, 0, false, 5, "", "", false, Excel.XlPlatform.xlWindows, "", true, false, 0, true, false, false);
            Excel.Worksheet ObjSheet = (Excel.Worksheet)ObjWorkBook.Sheets[1];
            return ObjSheet;
        }
        private void ReadExel(Human hum, Excel.Worksheet ObjSheet, Word.Table ObjWord)
        {
            for (int i = 2; i < ObjSheet.UsedRange.Rows.Count + 1; i++)
            {
                hum.Init(ObjSheet.Cells[i, 2].Text, ObjSheet.Cells[i, 3].Text, ObjSheet.Cells[i, 4].Text, ObjSheet.Cells[i, 5].Text);
                ReadWord(hum, ObjWord);
            }
            ExcelApp.Quit();
        }
        private Word.Table OpenWord()
        {
            WordApp = new Word.Application();
            Object FileName = openFileDialog2.FileName;
            WordApp.Documents.Open(ref FileName);
            Word.Document ObjDoc = WordApp.ActiveDocument;
            Word.Table ObjTable = ObjDoc.Tables[3];
            return ObjTable;
        }
        private void ReadWord(Human hum, Word.Table ObjTable)
        {
            int NumberOfMans = 1;
            for (int i = 2; i < ObjTable.Rows.Count + 1; i++)
            {
                if (ObjTable.Cell(i, 1).Range.Text.Trim('\a', '\r', '\n', '\t') == NumberOfMans.ToString())
                {
                    if (hum.Comparison(ObjTable.Cell(i, 2).Range.Text.Trim('\a', '\r', '\n', '\t'), ObjTable.Cell(i, 3).Range.Text.Trim('\a', '\r', '\n', '\t')))
                    {
                        hum.Write(WordAppRes, Convert.ToInt32(NumberOfMans));
                    }
                    Convert.ToInt32(NumberOfMans);
                    NumberOfMans++;
                }
            }
        }

        private void SaveRes()
        {
            Word.Document WordRes = WordAppRes.Documents[1];
            object fileName = @"D:\Resultit.docx";
            WordRes.SaveAs(ref fileName);
        }
        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
