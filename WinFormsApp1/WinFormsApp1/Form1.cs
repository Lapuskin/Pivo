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
                if (fstName == names[0] && lstName == names[1] && fathName == names[2] && date == dateTwo)
                    return true;
                else
                    return false;
            } 
            public void Write(Excel.Application ExcelApp, int i)
            {
                Excel.Workbooks ExelWorkbooks = ExcelApp.Workbooks;
                Excel.Workbook ExelWorkbookRes = ExelWorkbooks[1];
                Excel.Worksheet ExelSheetRes = (Excel.Worksheet)ExelWorkbookRes.Sheets[1];
                ExelSheetRes.Cells[i, 2].Value2 = fstName;
                ExelSheetRes.Cells[i, 3].Value2 = lstName;
                ExelSheetRes.Cells[i, 4].Value2 = fathName;
                ExelSheetRes.Cells[i, 5].Value2 = date;
            }
        }

        private Excel.Application ExcelApp;
        private Word.Application WordApp;
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
            ExcelApp = new Excel.Application();
            ExcelApp.Visible = true;
            ExcelApp.SheetsInNewWorkbook = 1;
            ExcelApp.DisplayAlerts = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            CreateTableRes();
            Excel.Worksheet ExcelName = OpenExcel();
            Word.Table WordName = OpenWorld();
            ReadExel(hum, ExcelName, WordName);
            SaveRes();
            MessageBox.Show("Успех! Ищите файл на рабочем столе.");
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
                hum.Init(ObjSheet.Cells[i, 2].Value2, ObjSheet.Cells[i, 3].Value2, ObjSheet.Cells[i, 4].Value2, ObjSheet.Cells[i, 5].Value2);
                ReadWord(hum, ObjWord);
            }
        }
        private Word.Table OpenWorld()
        {
            WordApp = new Word.Application();
            Object FileName = openFileDialog2.FileName;
            WordApp.Documents.Open(ref FileName);
            Word.Document ObjDoc = WordApp.ActiveDocument;
            Word.Table ObjTable = ObjDoc.Tables[1];
            return ObjTable;
        }
        private void ReadWord(Human hum, Word.Table ObjTable)
        {
            int NumberOfMans = 1;
            for (
                int i = 2; i < ObjTable.Columns.Count + 1; i++)
            {
                if (ObjTable.Cell(i, 1).Range.Text.Trim('\a', '\r', '\n', '\t') == NumberOfMans.ToString())
                {
                    if (hum.Comparison(ObjTable.Cell(i, 2).Range.Text.Trim('\a', '\r', '\n', '\t'), ObjTable.Cell(i, 3).Range.Text.Trim('\a', '\r', '\n', '\t')))
                    {
                        hum.Write(ExcelApp, Convert.ToInt32(NumberOfMans));
                    }
                    Convert.ToInt32(NumberOfMans);
                    NumberOfMans++;
                }
            }
        }

        private void SaveRes()
        {
            Excel.Workbooks ExelWorkbooks = ExcelApp.Workbooks;
            Excel.Workbook ExelWorkbookRes = ExelWorkbooks[1];
            ExcelApp.DefaultSaveFormat = Excel.XlFileFormat.xlExcel9795;
            ExcelApp.DisplayAlerts = true;
            ExelWorkbookRes.Saved = true;
            ExelWorkbookRes.Save();
        }
        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
