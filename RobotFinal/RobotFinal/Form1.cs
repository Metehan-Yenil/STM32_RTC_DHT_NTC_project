using System;
using System.IO.Ports; 
using System.Windows.Forms;
using System.Text;
using System.Threading; 
using System.Threading.Tasks;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
namespace RobotFinal
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort;
        private StringBuilder alinanVeribuffer = new StringBuilder();

        public Form1()
        {
            InitializeComponent();
            InitializeSerialPort();
        }

        private void InitializeSerialPort()
        {
            serialPort = new SerialPort("COM3", 9600, Parity.None, 8, StopBits.One);
            serialPort.DataReceived += SerialPort_DataReceived;
            serialPort.ErrorReceived += SerialPort_ErrorReceived;
            try
            {
                serialPort.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show("serial port baðlanma hatasý: " + ex.Message);
            }
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string data = serialPort.ReadExisting();
            alinanVeribuffer.Append(data);

            Task.Run(() =>
            {
                if (IsDataComplete(alinanVeribuffer.ToString()))
                {
                    string completeData = ExtractDataBetweenBrackets(alinanVeribuffer.ToString());
                    if (!string.IsNullOrEmpty(completeData))
                    {
                        this.Invoke(new Action(() =>
                        {
                            ProcessIncomingData(completeData);
                        }));
                    }
                    alinanVeribuffer.Clear();
                }
            });
        }

        private string ExtractDataBetweenBrackets(string data)
        {
            int startIndex = data.IndexOf('<');
            int endIndex = data.IndexOf('>');
            if (startIndex >= 0 && endIndex > startIndex)
            {
                return data.Substring(startIndex + 1, endIndex - startIndex - 1);
            }
            return string.Empty;
        }

        private void ProcessIncomingData(string data)
        {
            string[] splitData = data.Split(' ');
            if (splitData.Length > 0) lblReceivedData.Text = splitData[0];
            if (splitData.Length > 1) label4.Text = splitData[1];
            if (splitData.Length > 2) label5.Text = splitData[2];
            if (splitData.Length > 3) lblTarihSaat.Text = "Tarih ve Saat: " + splitData[3];
            if (splitData.Length > 4) label6.Text = splitData[4];
        }

        private bool IsDataComplete(string data)
        {
            return data.Contains("<") && data.Contains(">");
        }

        private void SerialPort_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            MessageBox.Show("seri baðlantýda hata.");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string tarihSaat = DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss");
            lblTarihSaat.Text = "Tarih ve Saat: " + tarihSaat;
        }

        private void btnTarihSaatAyarla_Click(object sender, EventArgs e)
        {
            if (!serialPort.IsOpen)
            {
                MessageBox.Show("seri port açýk deðil");
                return;
            }

            try
            {
                DateTime tarihSaat = DateTime.Now;
                string veri = tarihSaat.ToString("ddMMyyHHmmss") + "\n";
                serialPort.Write(veri);
                MessageBox.Show("Data sent: " + veri);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Veri gönderilirken hata olustu " + ex.Message);
            }
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            if (serialPort.IsOpen)
                serialPort.Close();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

            string tarihSaat = DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss");
            lblTarihSaat.Text = "Tarih ve Saat: " + tarihSaat;
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
    }
}

