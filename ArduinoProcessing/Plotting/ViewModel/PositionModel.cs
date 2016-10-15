using System;
using OxyPlot;
using OxyPlot.Series;
using System.Windows.Input;
using Prism.Commands;
using ArduinoProcessing;
using System.Collections.Generic;
using System.Windows.Threading;
using System.ComponentModel;

namespace Plotting.ViewModel
{
    class PositionModel : INotifyPropertyChanged
    {
        public ICommand AlphaChanged { get; set; }
        public PlotModel RawAccModel { get; private set; }
        public PlotModel FilteredAccModel { get; private set; }
        public PlotModel VelModel { get; private set; }
        public PlotModel PosModel { get; private set; }
        public event PropertyChangedEventHandler PropertyChanged;

        public float Alpha { get; set; }
        public float XOffset { get; set; }
        public float YOffset { get; set; }
        public float ZOffset { get; set; }
        public float XRotation { get; set; }
        public float YRotation { get; set; }
        public float ZRotation { get; set; }
        public int CurFrame  {get; set;}

        DataHandler dataHandler;
        DispatcherTimer animationTimer;
        TimeSpan animationTime = TimeSpan.FromMilliseconds(50);
        List<Vector3> position;
        List<Vector3> rotation;

        public PositionModel()
        {
            dataHandler = CSVHandler.Read("../../../../movement3.csv");
            
            this.RawAccModel = new PlotModel { Title = "Raw Acceleration Data" };
            this.FilteredAccModel = new PlotModel { Title = "Filtered Acceleration Data" };
            this.VelModel = new PlotModel { Title = "Filtered Velocity Data" };
            this.PosModel = new PlotModel { Title = "Filtered Position Data" };
            FillModel(dataHandler.Positions, RawAccModel);
            ComputeAndFill();

            AlphaChanged = new DelegateCommand(OnAlphaChanged);

            CurFrame = 0;
            animationTimer = new DispatcherTimer(DispatcherPriority.Normal)
            {
                Interval = animationTime,
            };

            animationTimer.Tick += animationTimer_Tick;
            animationTimer.Start();
        }

        protected void OnPropertyChanged(string name)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(name));
            }
        }

        public void OnAlphaChanged()
        {
            animationTimer.Stop();
            CurFrame = 0;
            ComputeAndFill();
            this.FilteredAccModel.InvalidatePlot(true);
            this.VelModel.InvalidatePlot(true);
            this.PosModel.InvalidatePlot(true);
            animationTimer.Start();
        }

        void animationTimer_Tick(object sender, EventArgs e)
        {
            XOffset = position[CurFrame].X;
            YOffset = position[CurFrame].Y;
            ZOffset = position[CurFrame].Z;
            XRotation = rotation[CurFrame].X;
            YRotation = rotation[CurFrame].Y;
            ZRotation = rotation[CurFrame].Z;

            CurFrame = (CurFrame + 1) % position.Count;

            OnPropertyChanged("XOffset");
            OnPropertyChanged("YOffset");
            OnPropertyChanged("ZOffset");
            OnPropertyChanged("XRotation");
            OnPropertyChanged("YRotation");
            OnPropertyChanged("ZRotation");
            OnPropertyChanged("CurFrame");
        }

        private void ComputeAndFill()
        {
            var filtered = dataHandler.FilterAcc(Alpha);
            var velocity = dataHandler.Integrate(filtered);
            position = dataHandler.Integrate(velocity);
            rotation = dataHandler.Rotations;
            FillModel(filtered, FilteredAccModel);
            FillModel(velocity, VelModel);
            FillModel(position, PosModel);
        }

        private void FillModel(List<Vector3> source, PlotModel model)
        {
            var xs = new List<DataPoint>();
            var ys = new List<DataPoint>();
            var zs = new List<DataPoint>();

            for (int i = 0; i < source.Count; i++)
            {
                xs.Add(new DataPoint(i, source[i].X));
                ys.Add(new DataPoint(i, source[i].Y));
                zs.Add(new DataPoint(i, source[i].Z));
            }

            model.Series.Clear();
            model.Series.Add(CreateSeries(xs, "X-Axis"));
            model.Series.Add(CreateSeries(ys, "Y-Axis"));
            model.Series.Add(CreateSeries(zs, "Z-Axis"));
        }

        private static LineSeries CreateSeries(List<DataPoint> xs, string title)
        {
            var xSeries = new LineSeries();
            xSeries.ItemsSource = xs;
            xSeries.Title = title;
            return xSeries;
        }
    }

}
