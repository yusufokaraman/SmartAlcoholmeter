using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Drawing.Drawing2D;

namespace parmak_izi_proje
{
   
    public partial class Form1 : Form
    {
        
        private void SetMyButtonIcon()
        {
            
        }
        public string[] ports = SerialPort.GetPortNames();
        
        static public string stm32_received_data;
        public SerialPort sp1=new SerialPort();
        public string form2_finger = "";

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            comboBox1.Items.AddRange(ports);
            SetMyButtonIcon();
        }
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }
        private void button1_Click(object sender, EventArgs e)
        {
            int num = new int();
            num = int.Parse(comboBox2.SelectedItem.ToString()); ; //burada string olan bir değişkeni integer olarak ayarlıyoruz

            try
            {
                serialPort1.PortName = comboBox1.SelectedItem.ToString();
                serialPort1.BaudRate = num;
                serialPort1.ReadTimeout = 200000;
                serialPort1.WriteTimeout = 200000;


                serialPort1.Open();

                if (!serialPort1.IsOpen)
                    serialPort1.Open();
                Thread.Sleep(200);
                serialPort1.BaseStream.Flush();

            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            if (serialPort1.IsOpen)
            {
                MessageBox.Show("Seri porta bağlantı Sağlandı", "Bildirim", MessageBoxButtons.OKCancel);
            }
            
            sp1 = serialPort1;
            
               if (serialPort1.IsOpen)
              {
                  MessageBox.Show("Seri porta bağlantı Sağlandı", "Bildirim", MessageBoxButtons.OK);
                //serialPort1.Close();
                this.Hide();
                Form2 F2 = new Form2();
                
                F2.serial_form_2_port = serialPort1;
                F2.isim = textBox2.Text;
                F2.Closed += (s, args) => this.Close();
                F2.Show();
                  
            }
              
        }
       

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void button3_Click(object sender, EventArgs e)
        {
           
            int MyInt = 1;
            byte[] b = BitConverter.GetBytes(MyInt);
            serialPort1.Write(b, 0, 1);
         

           // serialPort1.Write("1");
        }
      

        private void listBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {
          
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Form2 Project_dialog = new Form2();
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                MessageBox.Show("Port şuan Kapatıldı", "Hata", MessageBoxButtons.OK);
            }
            else
            {
                MessageBox.Show("Port şuan kullanılmıyor", "Hata", MessageBoxButtons.OK);
               
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int MyInt = 2;
            byte[] b = BitConverter.GetBytes(MyInt);
            serialPort1.Write(b, 0, 1);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int MyInt = 3;
            byte[] b = BitConverter.GetBytes(MyInt);
            serialPort1.Write(b, 0, 1);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

        }

      

       
        private void button6_Click(object sender, EventArgs e)
        {
            //textBox1.Clear();
        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {
          
        }

        private void comboBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click_1(object sender, EventArgs e)
        {

        }

        private void button7_Click(object sender, EventArgs e)
        {

        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            stm32_received_data = serialPort1.ReadExisting();
            this.Invoke(new EventHandler(F1_show_Form_data));
        }

        private void F1_show_Form_data(object sender, EventArgs e)
        {
           textBox1.Text += stm32_received_data + "\n\r";
            form2_finger = textBox1.Text;
            Thread.Sleep(200);
            if (textBox1.Lines.Length > 35)
                textBox1.Text = "";
        }
    }
}
