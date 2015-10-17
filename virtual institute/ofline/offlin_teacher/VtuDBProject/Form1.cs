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
    public partial class Form1 : Form
    {
        DataGrid dataval = new DataGrid();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "user" && textBox2.Text == "pass12345")
            {
                Form2 newform1 = new Form2();
                newform1.Show();
            }
            else
            {
                MessageBox.Show("Enter user name and password","Error");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
