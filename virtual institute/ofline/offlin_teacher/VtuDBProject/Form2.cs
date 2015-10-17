using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace VtuDBProject
{
    public partial class Form2 : Form
    {
        int serial = 0;
        public Form2()
        {
            InitializeComponent();
        }

      

        private void button1_Click_1(object sender, EventArgs e)
        {
            int nserial=serial;
            dataGridView1.Rows.Add();
            dataGridView1.Rows[serial].Cells[0].Value = ++nserial;
            dataGridView1.Rows[serial].Cells[1].Value = textBox1.Text;
            dataGridView1.Rows[serial].Cells[2].Value = textBox2.Text;
            dataGridView1.Rows[serial].Cells[3].Value = textBox3.Text;
            dataGridView1.Rows[serial].Cells[4].Value = textBox4.Text;
            dataGridView1.Rows[serial].Cells[5].Value = textBox5.Text;
            dataGridView1.Rows[serial].Cells[6].Value = textBox6.Text;
            serial++;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            for (int row = 0; row < dataGridView1.Rows.Count; row++)
            {
                if (dataGridView1.Rows[row].Cells[2].Value.ToString() == textBox7.Text)
                {
                    MessageBox.Show("hi");
                }
            }
            
           
        }

        private void button5_Click(object sender, EventArgs e)
        {
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {
            comboBox1.Items.Add("Semester 1");
            comboBox1.Items.Add("Semester 2");
            comboBox1.Items.Add("Semester 3");
            comboBox1.Items.Add("Semester 4");
            comboBox1.Items.Add("Semester 5");
            comboBox1.Items.Add("Semester 6");
            comboBox1.Items.Add("Semester 7");
            comboBox1.Items.Add("Semester 8");


        }

        private void button5_Click_1(object sender, EventArgs e)
        {
            Form3 form = new Form3();

            form.Show();
            /*
            for (int row = 0; row < dataGridView1.Rows.Count; row++)
            {
                if (dataGridView1.Rows[row].Cells[2].Value.ToString() == textBox7.Text && dataGridView1.Rows[row].Cells[2].Value.ToString() == textBox7.Text)
                {
                    MessageBox.Show("hi");
                }
            }*/
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            if (trackBar1.Value == 1)
            {
                textBox10.Text = "Excellent";
            }
            else if (trackBar1.Value == 2)
            {
                textBox10.Text = "Good";
            }
            else if (trackBar1.Value == 3)
            {
                textBox10.Text = "Average";
            }

            else if (trackBar1.Value == 4)
            {
                textBox10.Text = "Bad";
            }
            else
            {
                textBox10.Text = "Worst";
            }



        }

        private void tabPage3_Click(object sender, EventArgs e)
        {
            comboBox2.Items.Add("Yes");
            comboBox2.Items.Add("No");
            comboBox2.Items.Add("Neither");
            comboBox3.Items.Add("Yes");
            comboBox3.Items.Add("No");
            comboBox3.Items.Add("Neither");
            comboBox4.Items.Add("Yes");
            comboBox4.Items.Add("No");
            comboBox4.Items.Add("Neither");
            comboBox5.Items.Add("Yes");
            comboBox5.Items.Add("No");
            comboBox5.Items.Add("Neither");
            comboBox6.Items.Add("Yes");
            comboBox6.Items.Add("No");
            comboBox6.Items.Add("Neither");
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            richTextBox2.Text += "According to student feedback"+Environment.NewLine;
            richTextBox2.Text += "\nLecturer attending classes ? "+comboBox2.Text;
            richTextBox2.Text += "\nAre you clear with concept ? " + comboBox3.Text;
            richTextBox2.Text += "\nEqual preference for students ? " + comboBox4.Text;
            richTextBox2.Text += "\nLecturer using local language while teaching ? " + comboBox5.Text;
            richTextBox2.Text += "\nNotes given by lecturers resonable ? " + comboBox6.Text;
            richTextBox2.Text += "\nLecturer Rating : "+textBox10.Text;

            if (textBox9.Text != null)
            {
                richTextBox2.Text += "\nWritten feedback : " + textBox9.Text;
            }
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows[0].Cells[0].Value = "1";
            dataGridView1.Rows[0].Cells[1].Value = "Guru Charan";
            dataGridView1.Rows[0].Cells[2].Value = "1vk12cs016";
            dataGridView1.Rows[0].Cells[3].Value = "7";
            dataGridView1.Rows[0].Cells[4].Value = "cse";
            dataGridView1.Rows[0].Cells[5].Value = "gurucharan@gmail.com";
            dataGridView1.Rows[0].Cells[6].Value = "+91 - 999999999";
            
            dataGridView1.Rows[1].Cells[1].Value = "1";
            dataGridView1.Rows[1].Cells[2].Value = "GuruTej";
            dataGridView1.Rows[1].Cells[3].Value = "1vk12cs066";
            dataGridView1.Rows[1].Cells[4].Value = "7";
            dataGridView1.Rows[1].Cells[5].Value = "cse";
            dataGridView1.Rows[1].Cells[6].Value = "gurucharantej@gmail.com";
            dataGridView1.Rows[1].Cells[5].Value = "+91 - 999999669";
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void button8_Click(object sender, EventArgs e)
        {
            saveFileDialog1.InitialDirectory = "C:";
            saveFileDialog1.Title = "save file";
            saveFileDialog1.FileName = "pi";
            saveFileDialog1.Filter = "Excel file |*.xls|ping|*.xlsx";
            try
            {
                if (saveFileDialog1.ShowDialog() != DialogResult.Cancel)
                {
                    Microsoft.Office.Interop.Excel.Application excelapp = new Microsoft.Office.Interop.Excel.Application();
                    excelapp.Application.Workbooks.Add(Type.Missing);

                    excelapp.Columns.ColumnWidth = 20;

                    for (int i = 1; i < dataGridView1.Columns.Count + 1; i++)
                    {
                        excelapp.Cells[1, i] = dataGridView1.Columns[i - 1].HeaderText;
                    }

                    for (int i = 0; i < dataGridView1.Rows.Count; i++)
                    {
                        for (int j = 0; j < dataGridView1.Rows.Count; j++)
                        {
                            excelapp.Cells[i + 2, j + 1] = dataGridView1.Rows[i].Cells[j].Value.ToString();
                        }
                    }

                    excelapp.ActiveWorkbook.SaveCopyAs(saveFileDialog1.FileName.ToString());
                    excelapp.ActiveWorkbook.Saved = true;
                    excelapp.Quit();


                }
            }
            catch (Exception)
            {

            }
        }
    }
}
