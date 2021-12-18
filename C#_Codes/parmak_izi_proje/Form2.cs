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
using System.IO;
using System.Threading;
using System.Drawing.Drawing2D;
using System.Net.Http;
using System.Net;
//using Newtonsoft.Json;
using System.Data.OleDb;

namespace parmak_izi_proje
{
    public partial class Form2 : Form
    {
        public SerialPort serial_form_2_port;
        private void SetMyButtonIcon()
        {
        }
        Form1 STM32_Form_2 = new Form1();
        
       
        public string form2_serial_data= Form1.stm32_received_data;
        string[] ports = SerialPort.GetPortNames();
        public string isim = " ";
        int index = 4;
        bool alcohol_bool = false, heart_pulse_bool = true;
        public Form2()
        {
            InitializeComponent();
            
        }



        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            int MyInt = 1;
            byte[] b = BitConverter.GetBytes(MyInt);
            serial_form_2_port.Write(b, 0, 1);
            
        }

        private void Form2_Load(object sender, EventArgs e)
        {/*
            WebRequest request = WebRequest.Create("http://localhost/csalldatas.php");
 
             request.Method = "GET";
            request.Credentials = CredentialCache.DefaultCredentials;
            WebResponse response = request.GetResponse();
            Stream stream = response.GetResponseStream();
            using (StreamReader reader = new StreamReader(stream))
            {
                List<Kisi> kisiler = JsonConvert.DeserializeObject<List<Kisi>>(reader.ReadToEnd());
                label3.Text = kisiler[0].nabiz.ToString();

            }*/

            OleDbConnection connection = new OleDbConnection("Provider = Microsoft.ACE.Oledb.16.0; Data Source = proje1.accdb");
            OleDbCommand command = new OleDbCommand();
            connection.Open();
            command.Connection = connection;
            command.CommandText = "insert into Smart_alcoholmeter (isim) values (@isim)";
            command.Parameters.AddWithValue("@isim", isim);
            command.ExecuteNonQuery();
            connection.Close();
            serial_form_2_port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
            enable_button(index);
            // Boolean seri_port_check = true;
        }

        
        private async void F2_show_Form_data(object sender, EventArgs e)
        {

            Finger_list.Text +=form2_serial_data;
            Thread.Sleep(200);
            if (index == 3)
            {
               // int sayac = 0;
                string parmakizi = "";
                while (STM32_Form_2.form2_finger.Length >= 2) ;

                int wait_ıd = 9;
                byte[] ba = BitConverter.GetBytes(wait_ıd);
              //  while (sayac < 5)
              //  {
                    //sayac++;
                    serial_form_2_port.Write(ba, 0, 1);
               // }
                for (int i = 0; i <form2_serial_data.Length; i++)
                {
                    if (Char.IsDigit(form2_serial_data[i]))
                        parmakizi +=form2_serial_data[i];

                }
               

                DialogResult fingerprint_database = MessageBox.Show("Do you want to save this fingerprint ?\r\n" + parmakizi.Trim(), "Attention", MessageBoxButtons.YesNo);
                if (fingerprint_database == DialogResult.Yes)
                {
                    Thread.Sleep(200);
                    int buzzer = 5;
                    label3.Visible = true;
                    label3.Text = "OKAY";
                    label3.ForeColor = System.Drawing.Color.Green;

                    byte[] bytebuz = BitConverter.GetBytes(buzzer);
                    serial_form_2_port.Write(bytebuz, 0, 1);



                    DialogResult fingerprint_database2 = MessageBox.Show("do you want to save your fingerprint to database?", "attention", MessageBoxButtons.YesNo);
                    if (fingerprint_database2 == DialogResult.Yes)
                    {
                        int finger_regis = 5;
                        byte[] finger_Data_base = BitConverter.GetBytes(finger_regis);
                        serial_form_2_port.Write(finger_Data_base, 0, 1);
                        MessageBox.Show("Fingerprint ID saved to Database \r\n Registration performed successfully");

                        OleDbConnection connection = new OleDbConnection("Provider = Microsoft.ACE.Oledb.16.0; Data Source = proje1.accdb");
                        OleDbCommand command = new OleDbCommand();
                        connection.Open();
                        command.Connection = connection;
                        command.CommandText = "update Smart_alcoholmeter set parmak=@parmak where isim=@isim";
                        command.Parameters.AddWithValue("@parmak", parmakizi.Trim());
                        command.Parameters.AddWithValue("@isim", isim);
                        command.ExecuteNonQuery();
                        connection.Close();
                        index++;
                        label3.Visible = false;

                        enable_button(index);
                        int MyInt = 6;
                        byte[] b = BitConverter.GetBytes(MyInt);
                        serial_form_2_port.Write(b, 0, 1);

       

                    }
                    else
                    {
                        DialogResult Card_ID = MessageBox.Show("Fingerprint did not save to database\r\n Do you want to try again?", "attention", MessageBoxButtons.YesNo);

                        if (Card_ID == DialogResult.No)
                        {
                            index++;
                            enable_button(index);
                            label3.Visible = false;

                    }
                        if (Card_ID == DialogResult.Yes)
                        {
                            int MyInt = 1;
                            byte[] b = BitConverter.GetBytes(MyInt);
                            serial_form_2_port.Write(b, 0, 1);
                        }
                    }
                }
                else
                {
                    int MyInt = 1;
                    byte[] b = BitConverter.GetBytes(MyInt);
                    serial_form_2_port.Write(b, 0, 1);
                }
            }
            else if (index == 0)
            {
                DialogResult fingerprint_database = MessageBox.Show("Do you want to save this Card ID ?\r\n" +form2_serial_data.Trim(), "Attention", MessageBoxButtons.YesNo);
                if (fingerprint_database == DialogResult.Yes)
                {
                    int buzzer = 5;
                    label3.Visible = true;
                    label3.Text = "OKEY";
                    label3.ForeColor = System.Drawing.Color.Green;

                    byte[] bytebuz = BitConverter.GetBytes(buzzer);
                    serial_form_2_port.Write(bytebuz, 0, 1);

                    DialogResult fingerprint_database2 = MessageBox.Show("do you want to save your Card ID to database?", "attention", MessageBoxButtons.YesNo);
                    label3.Visible = false;
                    if (fingerprint_database2 == DialogResult.Yes)
                    {

                        OleDbConnection connection = new OleDbConnection("Provider = Microsoft.ACE.Oledb.16.0; Data Source = proje1.accdb");
                        OleDbCommand command = new OleDbCommand();
                        connection.Open();
                        command.Connection = connection;
                        command.CommandText = "update Smart_alcoholmeter set rfid=@rfid where isim=@isim";
                        command.Parameters.AddWithValue("@rfid",form2_serial_data.Trim());
                        command.Parameters.AddWithValue("@isim", isim);
                        command.ExecuteNonQuery();
                        connection.Close();
                        index++;
                        enable_button(index);

                        int MyInt = 6;
                        byte[] b = BitConverter.GetBytes(MyInt);
                        serial_form_2_port.Write(b, 0, 1);
                    }
                    else
                    {
                        DialogResult Card_ID = MessageBox.Show("Card ID did not save to database\r\n Do you want to try again?", "attention", MessageBoxButtons.YesNo);

                        if (Card_ID == DialogResult.No)
                        {
                            index++;
                            enable_button(index);
                        }
                        if (Card_ID == DialogResult.Yes)
                        {
                            int MyInt = 2;
                            byte[] b = BitConverter.GetBytes(MyInt);
                            serial_form_2_port.Write(b, 0, 1);
                        }
                    }

                }
                else
                {
                    int MyInt = 2;
                    byte[] b = BitConverter.GetBytes(MyInt);
                    serial_form_2_port.Write(b, 0, 1);
                }
               
            }
            else if (index == 1)
            {
                label4.Visible = true;
                label4.Text = "Alcohol value=%" +form2_serial_data.Trim();
                label4.ForeColor = System.Drawing.Color.Green;

                DialogResult fingerprint_database = MessageBox.Show("Is this value high?=\r\n" +form2_serial_data.Trim(), "Attention", MessageBoxButtons.YesNoCancel);


                if (fingerprint_database == DialogResult.Yes)
                {
                    alcohol_bool = true;

                    int alcohol_buz= 10;
                    byte[] b1 = BitConverter.GetBytes(alcohol_buz);
                    serial_form_2_port.Write(b1, 0, 1);

                    MessageBox.Show("High Alcohol value", "attention", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    DialogResult fingerprint_database2 = MessageBox.Show("do you want to save your Alcohol value to database?", "attention", MessageBoxButtons.YesNo);
                    if (fingerprint_database2 == DialogResult.Yes)
                    {

                        OleDbConnection connection = new OleDbConnection("Provider = Microsoft.ACE.Oledb.16.0; Data Source = proje1.accdb");
                        OleDbCommand command = new OleDbCommand();
                        connection.Open();
                        command.Connection = connection;
                        command.CommandText = "update Smart_alcoholmeter set alkol=@alkol where isim=@isim";
                        command.Parameters.AddWithValue("@alkol",form2_serial_data.Trim());
                        command.Parameters.AddWithValue("@isim", isim);
                        command.ExecuteNonQuery();
                        connection.Close();
                        index++;
                        enable_button(index);

                        
                        int MyInt = 6;
                        byte[] b = BitConverter.GetBytes(MyInt);
                        serial_form_2_port.Write(b, 0, 1);
                        
                    }
                    else
                    {
                        DialogResult alcohol = MessageBox.Show("alcohol value did not save to database\r\n Do you want to try again?", "attention", MessageBoxButtons.YesNo);

                        if (alcohol == DialogResult.No)
                        {
                            index++;
                            enable_button(index);
                        }
                        if (alcohol == DialogResult.Yes)
                        {
                            int MyInt = 3;
                            byte[] b = BitConverter.GetBytes(MyInt);
                            serial_form_2_port.Write(b, 0, 1);
                        }
                    }
                }
                else
                {
                    index++;
                    enable_button(index);

                    int MyInt = 8;
                    byte[] b = BitConverter.GetBytes(MyInt);
                    serial_form_2_port.Write(b, 0, 1);

                    MessageBox.Show("Alcohol Free", "Attention", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            else if (index == 2)
            {

                label5.Visible = true;
                label5.Text = "Heart Pulse=%" +form2_serial_data.Trim();
                label5.ForeColor = System.Drawing.Color.Green;

                DialogResult fingerprint_database = MessageBox.Show("Is this Heart Pulse value high ?" +form2_serial_data.Trim(), "Attention", MessageBoxButtons.YesNo);

                if (fingerprint_database == DialogResult.Yes)
                {
                    heart_pulse_bool = true;

                    MessageBox.Show("HIGH HEART PULSE VALUE", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    DialogResult fingerprint_database2 = MessageBox.Show("do you want to save your Heart Pulse value to database?", "attention", MessageBoxButtons.YesNo);
                    if (fingerprint_database2 == DialogResult.Yes)
                    {

                        label4.Visible = false;
                        label5.Visible = false;

                        int MyInt = 6;
                        byte[] b = BitConverter.GetBytes(MyInt);
                        serial_form_2_port.Write(b, 0, 1);

                        OleDbConnection connection = new OleDbConnection("Provider = Microsoft.ACE.Oledb.16.0; Data Source = proje1.accdb");
                        OleDbCommand command = new OleDbCommand();
                        connection.Open();
                        command.Connection = connection;
                        command.CommandText = "update Smart_alcoholmeter set nabiz=@nabiz where isim=@isim";
                        command.Parameters.AddWithValue("@nabiz",form2_serial_data.Trim());
                        command.Parameters.AddWithValue("@isim", isim);
                        command.ExecuteNonQuery();
                        connection.Close();
                        index++;
                        enable_button(index);

                    }
                    else
                    {
                        DialogResult heart_pulse = MessageBox.Show("Heart Pulse value did not save to database\r\n Do you want to try again?", "attention", MessageBoxButtons.YesNo);
                        label4.Visible = false;
                        label5.Visible = false;
                        if (heart_pulse == DialogResult.No)
                        {
                            index++;
                            enable_button(index);
                        }
                        if (heart_pulse == DialogResult.Yes)
                        {
                            int MyInt = 4;
                            byte[] b = BitConverter.GetBytes(MyInt);
                            serial_form_2_port.Write(b, 0, 1);
                        }
                    }
                    //MessageBox.Show("Heart Pulse value did not save to database");
                }
                else
                {
                    index++;
                    enable_button(index);

                    int MyInt = 8;
                    byte[] b = BitConverter.GetBytes(MyInt);
                    serial_form_2_port.Write(b, 0, 1);
                    MessageBox.Show("No Risk", "Attention", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                if (alcohol_bool && heart_pulse_bool)
                {
                    button7.Visible = true;
                }

            }



            Thread.Sleep(200);
           
            if (Finger_list.Lines.Length > 35)
                Finger_list.Text = "";
        }
        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            // form2_serial_data= serial_form_2_port.ReadExisting();
            // this.Invoke(new EventHandler(F2_show_Form_data));
            int datalength = serial_form_2_port.BytesToRead;
            if (datalength > 1)
            {
                form2_serial_data = serial_form_2_port.ReadExisting();

                this.Invoke(new EventHandler(F2_show_Form_data));
            }
        }
        private void label2_Click(object sender, EventArgs e)
        {
        }
        private void button5_Click(object sender, EventArgs e)
        {
            Finger_list.Clear();
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int MyInt = 2;
            byte[] b = BitConverter.GetBytes(MyInt);
            serial_form_2_port.Write(b, 0, 1);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int MyInt = 3;
            byte[] b = BitConverter.GetBytes(MyInt);
            serial_form_2_port.Write(b, 0, 1);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            int MyInt = 4;
            byte[] b = BitConverter.GetBytes(MyInt);
            serial_form_2_port.Write(b, 0, 1);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            MessageBox.Show("RISK !!!!!", "Attention", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            label4.Visible = false;
            label5.Visible = false;
            button7.Visible = false;
            int MyInt = 7;
            byte[] b = BitConverter.GetBytes(MyInt);
            serial_form_2_port.Write(b, 0, 1);
        }

        void enable_button(int index)
        {
            if (index == 0)
            {
                button2.Enabled = true;
                button1.Enabled = false;
                button3.Enabled = false;
                button6.Enabled = false;
            }
            if (index == 1)
            {
                button2.Enabled = false;
                button1.Enabled = false;
                button3.Enabled = true;
                button6.Enabled = false;
            }
            if (index == 2)
            {
                button2.Enabled = false;
                button1.Enabled = false;
                button3.Enabled = false;
                button6.Enabled = true;
            }
            if (index == 3)
            {
                button2.Enabled = false;
                button1.Enabled = true;
                button3.Enabled = false;
                button6.Enabled = false;
            }
            if (index == 4)
            {
                button2.Enabled = false;
                button1.Enabled = true;
                button3.Enabled = false;
                button6.Enabled = false;
            }

        }
    }

}
