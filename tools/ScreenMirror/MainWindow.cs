using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        Bitmap buffer = null;
        Stopwatch sw = new Stopwatch();

        StringBuilder sb = new StringBuilder();
        double fps;

        bool pause = false;

        public Form1()
        {
            InitializeComponent();
            updateButton();
            
            serialPort1.Open();
            sw.Start();
        }

        void updateButton()
        {
            button1.Text = pause ? "Run" : "Stop";
            label1.Text = pause ? "Stoped" : "";
        }


        void Draw()
        {
            var data = sb.ToString().Trim(); 
            if (string.IsNullOrEmpty(data))
            {
                sb.Clear();
                return;
            }

            byte[] raw;

            try
            {
                raw = data.Split(' ').Select(x => FromHex(x)).ToArray();
            }
            catch (Exception x)
            {
                Debug.Print(x.ToString());
                sb.Clear();
                return;
            }

            if (raw.Length != 1024)
            {
                Debug.Print("invalid data");
                sb.Clear();
                return;
            }

            var b = new Bitmap(128, 64);

            for (var y = 0; y < 64 / 8; y++)
            {
                for (var x = 0; x < 128; x++)
                {
                    var f = raw[x + y * 128];

                    for (var i = 0; i < 8; i++)
                    {
                        var p = (f & 1 << i) != 0;
                        Color c;

                        if (p)
                        {
                            c = Color.Aqua;
                        }
                        else
                        {
                            c = Color.Black;
                        }

                        b.SetPixel(x, y * 8 + i, c);
                    }
                }
            }


            Debug.WriteLine(data.Length / 2);


            buffer = b;

            sb.Clear();


            fps = 1000d / sw.ElapsedMilliseconds;
            
            sw.Restart();

            panel1.Invalidate();

        }

        private static byte FromHex(string x)
        {
            return (byte)Convert.ToUInt32(x, 16);
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            if (buffer == null) return;

            e.Graphics.DrawImage(buffer, 10, 10);
            label1.Text = $"{fps:F2} FPS";
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            

            while(serialPort1.BytesToRead > 0)
            {
                var b = serialPort1.ReadChar();

                if (pause) continue;

                if (b == '\r') continue;

                if (b == '\n')
                {
                    Draw();
                    continue;
                }

                sb.Append((char)b);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pause = !pause;
            updateButton();
        }

        private void button2_Click(object sender, EventArgs e)
        {


            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                var file = saveFileDialog1.FileName;

                Debug.Print(file);

                buffer.Save(file);
            }
        }
    }
}
