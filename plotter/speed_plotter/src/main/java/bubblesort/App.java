package bubblesort;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.knowm.xchart.BitmapEncoder;
import org.knowm.xchart.BitmapEncoder.BitmapFormat;
import org.knowm.xchart.SwingWrapper;
import org.knowm.xchart.XYChart;
import org.knowm.xchart.XYChartBuilder;
import org.knowm.xchart.XYSeries.XYSeriesRenderStyle;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class App {
	static void usage() {
		System.out.println("App <results json file> <another json file>");
	}

	public static void main(String[] args) throws IOException {
		if (args.length != 2) {
			usage();
			return;
		}

		String title = args[0] + " vs. " + args[1];

		XYChart c = new XYChartBuilder().width(600).height(480).title(title)
				.xAxisTitle("Vector Length").yAxisTitle("ns Taken").build();
		JSONParser jp = new JSONParser();
		
		for (int i = 0; i < 2; i++) {
			String fname = args[i];
			try (FileReader fr = new FileReader(fname)) {
				JSONObject json = (JSONObject) jp.parse(fr);
				JSONArray benchmarks = (JSONArray) json.get("benchmarks");

				ArrayList<BenchmarkRun> benchmarkRuns = new ArrayList<BenchmarkRun>();

				for (Object run : benchmarks) {
					JSONObject jrun = (JSONObject) run;
					String name = (String) jrun.get("run_name");
					Double real_time = (Double) jrun.get("real_time");
					benchmarkRuns.add(new BenchmarkRun(name, real_time));
				}

				List<Integer> xData = benchmarkRuns.stream()
						.map(BenchmarkRun::getElements)
						.collect(Collectors.toList());
				List<Double> yData = benchmarkRuns.stream()
						.map(BenchmarkRun::getNs_taken)
						.collect(Collectors.toList());

				c.addSeries(fname, xData, yData);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} catch (ParseException e) {
				e.printStackTrace();
			}
		}
		c.getStyler().setLegendVisible(true);
		c.getStyler().setDefaultSeriesRenderStyle(XYSeriesRenderStyle.Scatter);
		c.getStyler().setMarkerSize(10);

		new SwingWrapper(c).displayChart();

	}

}
