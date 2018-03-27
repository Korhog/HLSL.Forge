namespace HLSL.Elements
{
    using rMind.Nodes;
    using rMind.Elements;
    using rMind.Content.Row;
    using Windows.UI.Xaml.Media;
    using Windows.UI;
    using Windows.UI.Xaml;

    public class MathNodeBase : RowContainerBase
    {
        public MathNodeBase(rMindBaseController  parent) : base(parent)
        {
            m_template.ColumnDefinitions.Clear();

            m_template.ColumnDefinitions.Add(new Windows.UI.Xaml.Controls.ColumnDefinition { Width = GridLength.Auto });
            m_template.ColumnDefinitions.Add(new Windows.UI.Xaml.Controls.ColumnDefinition { Width = GridLength.Auto });
            m_template.ColumnDefinitions.Add(new Windows.UI.Xaml.Controls.ColumnDefinition { Width = GridLength.Auto });

            AddRow(new rMindRow
            {
                InputNode = new rMindBaseNode(this)
                {
                    Stroke = new SolidColorBrush(Colors.DeepSkyBlue),
                    NodeOrientation = rMindNodeOriantation.Left,
                    ConnectionType = rMindNodeConnectionType.Container,
                    Label = "A"
                },

                OutputNode = new rMindBaseNode(this)
                {
                    Stroke = new SolidColorBrush(Colors.White),
                    NodeOrientation = rMindNodeOriantation.Right,
                    ConnectionType = rMindNodeConnectionType.Container,
                    Label = "Out",
                    RowSpan = 2                    
                }
            });

            AddRow(new rMindRow
            {
                InputNode = new rMindBaseNode(this)
                {
                    Stroke = new SolidColorBrush(Colors.DeepSkyBlue),
                    NodeOrientation = rMindNodeOriantation.Left,
                    ConnectionType = rMindNodeConnectionType.Container,
                    Label = "B"
                },
                OutputNodeType = rMindNodeConnectionType.None
            });
        }
    }
}
